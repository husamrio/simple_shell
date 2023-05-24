#include "shell.h"

/**
 * printString - Prints a string to the standard output(*****Done)
 * @str: The string to be printed
 *
 * Return: void
 */
void printString(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		eputchar(str[i]);
		i++;
	}
}

/**
 * eputchar - writes the char 'c' to standard error(*****Done)
 * @c: The char to print
 *
 * Return: On Kufaulu 1.
 * On makosa, -1 inarudishwa, na errno inasetiwa kulingana.
 */
int eputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == FLUSH_BUFFER || index >= WRITE_BUF_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[index++] = c;
	return (1);
}


/**
 * write_character - writes the char c to the file descriptor(*****Done)
 * @c: The char to print
 * @fd: The file descriptor to write to
 *
 * Return: On success, 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == FLUSH_BUFFER || index >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[index++] = c;
	return (1);
}

/**
 * _putstr_fd - writes a string to a file descriptor(*****Done)
 * @str: the string to be written
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putstr_fd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count +=  write_character(*str++, fd);
	}

	return (count);
}

