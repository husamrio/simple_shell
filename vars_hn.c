#include "shell.h"

/**
 * isChain - checks if the current character in the(*****Done)
 * buffer is a chain delimiter
 * @info: parameter struct
 * @buffer: character buffer
 * @position: current position in the buffer address
 *
 * Return: 1 if chain delimit, 0 otherwise
 */
int isChain(data_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		info->commandbuffertype = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		info->commandbuffertype = CMD_AND;
	}
	else if (buffer[index] == ';') /* found end of this command */
	{
		buffer[index] = 0; /* replace semicolon with null */
		info->commandbuffertype = CMD_CHAIN;
	}
	else
		return (0);
	*position = index;
	return (1);
}

/**
 * contChain - checks if chaining should continue based on (*****Done)
 * the last status
 * @pInfo: the parameter struct
 * @bu: the char buffer
 * @cPos: address of current position in buffer
 * @stIdx: starting position in buffer
 * @len: len of buffer
 *
 * Return: void
 */
void contChain(data_t *pInfo, char *bu, size_t *cPos, size_t stIdx, size_t len)
{
	size_t newPos = *cPos;

	if (pInfo->commandbuffertype == CMD_AND)
	{
		if (pInfo->status)
		{
			bu[stIdx] = 0;
			newPos = len;
		}
	}
	if (pInfo->commandbuffertype == CMD_OR)
	{
		if (!pInfo->status)
		{
			bu[stIdx] = 0;
			newPos = len;
		}
	}

	*cPos = newPos;
}

/**
 * replaceAlias - Replaces aliases in the tokenized string(*****Done)
 * @data: The data structure containing the information
 *
 * Returns: 1 if replaced, 0 otherwise
 */
int replaceAlias(data_t *data)
{
	int i;
	list_t *curr;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		curr = findNode(data->alias, data->arguments[0], '=');
		if (!curr)
			return (0);
		free(data->arguments[0]);
		ptr = find_character(curr->str, '=');
		if (!ptr)
			return (0);
		ptr = betty_strdup(ptr + 1);
		if (!ptr)
			return (0);
		data->arguments[0] = ptr;
	}
	return (1);
}

/**
 * replaceVars - replaces variables in the tokenized string(*****Done)
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceVars(data_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->arguments[i]; i++)
	{
		if (info->arguments[i][0] != '$' || !info->arguments[i][1])
			continue;

		if (!betty_strcmp(info->arguments[i], "$?"))
		{
			updateString(&(info->arguments[i]),
				betty_strdup(convertNum(info->status, 10, 0)));
			continue;
		}
		if (!betty_strcmp(info->arguments[i], "$$"))
		{
			updateString(&(info->arguments[i]),
				betty_strdup(convertNum(getpid(), 10, 0)));
			continue;
		}
		node = findNode(info->env, &info->arguments[i][1], '=');
		if (node)
		{
			updateString(&(info->arguments[i]),
				betty_strdup(find_character(node->str, '=') + 1));
			continue;
		}
		updateString(&info->arguments[i], betty_strdup(""));

	}
	return (0);
}

/**
 * updateString - replaces a string with a new one(*****Done)
 * @original: pointer to the original string
 * @newString: pointer to the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int updateString(char **original, char *newString)
{
	free(*original);
	*original = newString;
	return (1);
}
