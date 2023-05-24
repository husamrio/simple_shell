#include "shell.h"

/**
 * printEnv - prints the current environment(*****Done)
 * @data: Struc cont potential argu. Used to maint
 *         constant funct prototype.
 * Return: Always 0
 */
int printEnv(data_t *data)
{
	display_list(data->env);
	return (0);
}

/**
 * getEnvValue - gets the value of an env variable(*****Done)
 * @data: Struct containing potent argum. Used to upkeep
 * @variable: environment variable name
 *
 * Return: the value of the environment variable
 */
char *getEnvValue(data_t *data, const char *variable)
{
	list_t *currentNode = data->env;
	char *pointer;

	while (currentNode)
	{
		pointer = _startsWith(currentNode->str, variable);
		if (pointer && *pointer)
			return (pointer);
		currentNode = currentNode->next;
	}
	return (NULL);
}

/**
 * set_environ - Initialize or modify an environment variable(*****Done)
 * @data: Structure containing possible arguments
 * Return: 0 on success, 1 on failure
 */
int set_environ(data_t *data)
{
	if (data->argc != 3)
	{
		printString("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(data, data->arguments[1], data->arguments[2]))
	return (0);
	return (1);
}

/**
 * removeEnvVar - Remove an environment variable(*****Done)
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int removeEnvVar(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		printString("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		EnvVaremove(data, data->arguments[i]);

	return (0);
}

/**
 * fillEnvList - populates environment linked list(*****Done)
 * @data: Struct contain potential argum. Used to upkeep
 *         const func prototype.
 * Return: All the time 0
 */
int fillEnvList(data_t *data)
{
	list_t *node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		addNodeEnd(&node, environ[index], 0);
	data->env = node;
	return (0);
}

