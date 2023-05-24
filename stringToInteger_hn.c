#include "shell.h"

/**
 * is_running_interactively - returns true if shell is running(***Done)
 *  in interactive mode
 * @info: Address struct
 *
 * Return: 1 if  running in interactive mode, 0 otherwise
 */
int is_running_interactively(data_t *info)
{
	return (isatty(STDIN_FILENO) != 0 && info->readfd <= 2);
}

/**
 * isChDel - checks character is a delimiter or not(***Done)
 * @c: the character to check
 * @delimiter: Delimiter string
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int isChDel(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == c)
			return (1);
		delimiter++;
	}
	return (0);
}

/**
 * isAlphabetic - checks if a character is alphabetic(***Done)
 * @c: the character to check
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * stringToInteger - converts a string to an integer(***Done)
 * @str: the string to be converted
 * Return: the converted integer if successful, 0 otherwise
 */
int stringToInteger(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
