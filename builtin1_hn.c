#include "shell.h"

/**
* display_hist - Displays the hist list, by line,(***Done)
* preceded with line numbers, starting at 0.
* @info: Struct containing potential arg. To maintain
* const funct prototype.
* Return: Always 0
*/
int display_hist(data_t *info)
{
display_list_elements(info->history);
return (0);
}

/**
 * removeAlias - removes an alias from the data structure(***Done)
 * @info: data structure containing the aliases
 * @alias: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int removeAlias(data_t *info, char *alias)
{
	char *equalSignPos, temp;
	int result;

	equalSignPos = find_character(alias, '=');
	if (!equalSignPos)
		return (1);
	temp = *equalSignPos;
	*equalSignPos = '\0';
	result = delete_node(&(info->alias),
		find_node_index(info->alias, findNode(info->alias, alias, -1)));
	*equalSignPos = temp;
	return (result);
}

/**
 * setAlias - sets alias to string(***Done)
 * @info: parameter struct
 * @aliasStr: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setAlias(data_t *info, char *aliasStr)
{
	char *ptr;

	ptr = find_character(aliasStr, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (removeAlias(info, aliasStr));

	removeAlias(info, aliasStr);
	return (addNodeEnd(&(info->alias), aliasStr, 0) == NULL);
}

/**
 * printAlias - prints an string Alias(***Done)
 * @listNode: the node Alias
 *
 * Return: 0 on success, 1 on error
 */
int printAlias(list_t *listNode)
{
	char *equalSign = NULL, *aliasValue = NULL;

	if (listNode)
	{
		equalSign = find_character(listNode->str, '=');
		for (aliasValue = listNode->str; aliasValue <= equalSign; aliasValue++)
			_write_char(*aliasValue);
		_write_char('\'');
		print_string(equalSign + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * myAlias - Simulates the alias builtin (man alias)(***Done)
 * @info: Structure containing potential arg. For maintaining
 *          constant func prototype.
 * Return: Always 0
 */
int myAlias(data_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->arguments[i]; i++)
	{
		ptr = find_character(info->arguments[i], '=');
		if (ptr)
			setAlias(info, info->arguments[i]);
		else
			printAlias(findNode(info->alias, info->arguments[i], '='));
	}

	return (0);
}

