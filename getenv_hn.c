#include "shell.h"

/**
 * envToStringArray - returns the copy of the string array(*****Done)
 * representing the environment
 * @data: Structure containing potential arguments. Used upkeep
 *         const funct prototype.
 * Return: Pointer to the string array
 */
char **envToStringArray(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = stringsFromList(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * EnvVaremove - Remove an envir var (*****Done)
 * @data: Struc containing potential argum. Used to upkeep
 *         const func prototype.
 * Return: 1 on delete, 0 else
 * @variable: the string env var property
 */
int EnvVaremove(data_t *data, char *variable)
{
	list_t *currentNode = data->env;
	size_t index = 0;
	char *p;

	if (!currentNode || !variable)
		return (0);

	while (currentNode)
	{
		p = _startsWith(currentNode->str, variable);
		if (p && *p == '=')
		{
			data->env_changed = delete_node(&(data->env), index);
			index = 0;
			currentNode = data->env;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}
	return (data->env_changed);
}

/**
 * set_env - Initia new env var,(*****Done)
 *             or modify an existing one
 * @info: Struct contain potential argume. Used to upkeep
 *        const funct prototype.
 * @var: string env var property
 * @value:string env var value
 *  Return: all the time 0
 */


int set_env(data_t *data, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);
	buffer = malloc(str_len(var) + str_len(value) + 2);
	if (!buffer)
		return (1);
	betty_strcpy(buffer, var);
	betty_str_concat(buffer, "=");
	betty_str_concat(buffer, value);
	node = data->env;
	while (node)
	{
		ptr = _startsWith(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(data->env), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
}

