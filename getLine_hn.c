#include "shell.h"

/**
 * buf_input - Reads input into a buffer
 * @data: Parameter struct
 * @buffer: Address of the buffer
 * @length: Address of length variable
 *
 * Return: Bytes read
 */
ssize_t buf_input(data_t *data, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t temp_length = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, blockSigint);
#if USE_GETLINE
		bytes_read = getline(buffer, &temp_length, stdin);
#else
		bytes_read = get_next_line(data, buffer, &temp_length);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0'; /* Remove trailing newline */
				bytes_read--;
			}
			data->line_count_flag = 1;
			shorten_string(*buffer);
			add_hist_entry(data, *buffer, data->hist_count++);
			/* if (find_character(*buffer, ';')) is this a command chain? */
			{
				*length = bytes_read;
				data->cmd_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * getLineInput - retrieves a line without the newline character
 * @data: data struct containing information
 *
 * Return: number of bytes read
 */
ssize_t getLineInput(data_t *data)
{
	static char *cmdbuf;
	static size_t v, k, length;
	ssize_t bytesRead = 0;
	char **commandPtr = &(data->arg), *ptr;

	_write_char(FLUSH_BUFFER);
	bytesRead = buf_input(data, &cmdbuf, &length);
	if (bytesRead == -1) /* EOF */
		return (-1);
	if (length) /* commands remaining in the chain buffer */
	{
		v = k; /* initialize new v to current buffer position */
		ptr = cmdbuf + k; /* get pointer for return */

		contChain(data, cmdbuf, &v, k, length);
		while (v < length) /* iterate until semicolon or end */
		{
			if (isChain(data, cmdbuf, &v))
				break;
			v++;
		}

		k = v + 1; /* increment past nullified ';' */
		if (k >= length) /* reached end of buffer? */
		{
			k = length = 0; /* reset position and length */
			data->cmd_buffer = CMD_NORM;
		}

		*commandPtr = ptr; /* pass back pointer to current command position */
		return (str_len(ptr)); /* return length of current command */
	}

	*commandPtr = cmdbuf; /* not a chain, pass back buffer from getLine() */
	return (bytesRead); /* return length of buffer from getLine() */
}


/**
 * readBuffer - reads buffer
 * @data: parameter struct of code
 * @buffer: the buffer
 * @size: the size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(data_t *data, char *buffer, size_t *size)
{
	ssize_t bytesRead = 0;

	if (*size)
	return (0);
		bytesRead = read(data->readfd, buffer, READ_BUF_SIZE);
		if (bytesRead >= 0)
		*size = bytesRead;
		return (bytesRead);
}

/**
 * get_next_line - reads the next line from standard input
 * @data: the parameter struct
 * @buffer: the address of the pointer to buffer, preallocated or NULL
 * @buffer_size: the size of the preallocated buffer if not NULL
 *
 * Return: length of the line read
 */
int get_next_line(data_t *data, char **buffer, size_t *buffer_size)
{
	static char buff[READ_BUF_SIZE];
	static size_t index, buffer_length;
	size_t line_len;
	ssize_t f = 0, li_re = 0;
	char *ptr = NULL, *new_ptr = NULL, *ch;

	ptr = *buffer;
	if (ptr && buffer_size)
		li_re = *buffer_size;
	if (index == buffer_length)
		index = buffer_length = 0;

	f = readBuffer(data, buff, &buffer_length);
	if (f == -1 || (f == 0 && buffer_length == 0))
		return (-1);

	ch = find_character(buff + index, '\n');
	line_len = ch ? 1 + (unsigned int)(ch - buff) : buffer_length;
	new_ptr = realloc_block(ptr, li_re, li_re ? li_re + line_len : line_len + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (li_re)
		string_nconcat(new_ptr, buff + index, line_len - index);
	else
		betty_strncpy(new_ptr, buff + index, line_len - index + 1);

	li_re += line_len - index;
	index = line_len;
	ptr = new_ptr;

	if (buffer_size)
		*buffer_size = li_re;
	*buffer = ptr;
	return (li_re);
}

/**
 * blockSigint - blocks ctrl-C
 * @signalNumber: the signal number
 *
 * Return: void
 */
void blockSigint(__attribute__((unused))int signalNumber)
{
	print_string("\n");
	print_string("♔ ♔ ♔ ");
	_write_char(FLUSH_BUFFER);
}

