#include "shell.h"

/**
 *  getHistFile - Retrieves the history file path(*****Done)
 * @dat: Parameter struct
 *
 *  Return: Allocated string containing the history file path
 */

char *getHistFile(data_t *data)
{
	char *buf, *dir;

	dir = getEnvValue(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	betty_strcpy(buf, dir);
	betty_str_concat(buf, "/");
	betty_str_concat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - File is created, or appended to an existing file(*****Done)
 * @data: The parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(data_t *data)
{
	ssize_t fd;
	char *fname = getHistFile(data);
	list_t *n = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (n = data->history; n; n = n->next)
	{
		_putstr_fd(n->str, fd);
		write_character('\n', fd);
	}
	write_character(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * read_hist -history read from file(*****Done)
 * @data: Parameter struct
 *
 * Return: hist_count on success, 0 otherwise
 */
int read_hist(data_t *d)
{
	int i, last = 0, count = 0;
	ssize_t file_desc, read_len, file_size = 0;
	struct stat stats;
	char *buffer = NULL, *file_name = getHistFile(d);

	if (!file_name)
		return (0);

	file_desc = open(file_name, O_RDONLY);
	free(file_name);
	if (file_desc == -1)
		return (0);
	if (!fstat(file_desc, &stats))
		file_size = stats.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_len = read(file_desc, buffer, file_size);
	buffer[file_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(file_desc);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			add_hist_entry(d, buffer + last, count++);
			last = i + 1;
		}
	if (last != i)
		add_hist_entry(d, buffer + last, count++);
	free(buffer);
	d->hist_count = count;
	while (d->hist_count-- >= HIST_MAX)
		delete_node(&(d->history), 0);
	update_history(d);
	return (d->hist_count);
}


/**
 * add_hist_entry - Entry is added to the history linked list(*****Done)
 * @d:Potential arguments structure containing. Used to upkeep the
 * @buffer: buffer
 * @count: the history linecount, hist_count
 *
 * Return: Always 0
 */
int add_hist_entry(data_t *d, char *buffer, int count)
{
	list_t *new_node = NULL;

	if (d->history)
		new_node = d->history;
	addNodeEnd(&new_node, buffer, count);

	if (!d->history)
		d->history = new_node;
	return (0);
}

/**
 * update_history - updates the history linked list after changes(*****Done)
 * @data:Potential arguments containing structures. Used to upkeep
 *
 * Return: new history_count
 */
int update_history(data_t *data)
{
	list_t *current_node = data->history;
	int index = 0;

	while (current_node)
	{
		current_node->num = index++;
		current_node = current_node->next;
	}

	return (data->hist_count = index);
}

