#include "shell.h"

/**
 * resetData - initializes data structure
 * @data: pointer to data_t struct
 */
void resetData(data_t *data)
{
	data->arg = NULL;
	data->arguments = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * init_data - initializes data structure
 * @data: pointer to data_t structure
 * @args: argument vector
 */
void init_data(data_t *data, char **args)
{
	int i = 0;

	data->filename = args[0];
	if (data->arg)
	{
		data->arguments = split_string(data->arg, " \t");
		if (!data->arguments)
		{
			data->arguments = malloc(sizeof(char *) * 2);
			if (data->arguments)
			{
				data->arguments[0] = betty_strdup(data->arg);
				data->arguments[1] = NULL;
			}
		}
		for (i = 0; data->arguments && data->arguments[i]; i++)
			;
		data->argc = i;

		replaceAlias(data);
		replaceVars(data);
	}
}

/**
 * freeData - frees fields of data_t struct
 * @data: the struct address
 * @freeAll: true if freeing all fields completely
 */
void freeData(data_t *data, int freeAll)
{
	free_string_array(data->arguments);
	data->arguments = NULL;
	data->path = NULL;
	if (freeAll)
	{
		if (!data->cmd_buffer)
			free(data->arg);
		if (data->env)
			clear_list(&(data->env));
		if (data->history)
			clear_list(&(data->history));
		if (data->alias)
			clear_list(&(data->alias));
		free_string_array(data->environ);
		data->environ = NULL;
		free_ptr((void **)data->cmd_buffer);
		if (data->readfd > 2)
			close(data->readfd);
		_write_char(FLUSH_BUFFER);
	}
}

