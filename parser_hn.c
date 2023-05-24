#include "shell.h"

/**
* isExecutableCommand - checks if a file is an executable command(*Done)
* @info: pointer to the info struct
* @path: path to the file
*
* Returns: 1 if the file is an executable command, 0 otherwise
*
*/
int isExecutableCommand(data_t *info, char *path)
{
	struct stat fileStat;

	(void)info;
	if (!path || stat(path, &fileStat))
	return (0);

	if (fileStat.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * duplicateSubstring - duplicates a substring
 * @str: the string to extract substring from
 * @start: starting index of the substring
 * @stop: stopping index of the substring (exclusive)
 *
 * Returns: the pointer to buffer the duplicated substring
 *
 */
char *duplicateSubstring(char *str, int start, int stop)
{
	static char buffer[1024];
	int index = 0, m = 0;

	for (m = 0, index = start; index < stop; index++)
	{
		if (str[index] != ':')
		buffer[m++] = str[index];
	}

	buffer[m] = 0;

	return (buffer);
}


/**
 * findExecutablePath - finds the full path of a command in the PATH string
 * @info: pointer to the info struct
 * @pathString: the PATH string
 * @command: the command to find
 *
 * Return: the full path of the command if found, or NULL otherwise
 *
 */
char *findExecutablePath(data_t *info, char *pathString, char *command)
{
	int index = 0, startPos = 0;
	char *path;

	if (!pathString)
		return (NULL);
	if ((str_len(command) > 2) && _startsWith(command, "./"))
	{
		if (isExecutableCommand(info, command))
			return (command);
	}

	while (1)
	{
		if (!pathString[index] || pathString[index] == ':')
		{
			path = duplicateSubstring(pathString, startPos, index);
			if (!*path)
				betty_str_concat(path, command);
			else
			{
				betty_str_concat(path, "/");
				betty_str_concat(path, command);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathString[index])
				break;
			startPos = index;
		}
		index++;
	}

	return (NULL);
}
