#include "shell.h"

/**
 * betty_strcpy - Copies a string.(*****Done)
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination string.
 */
char *betty_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * betty_strdup - Duplicates a string.(*****Done)
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *betty_strdup(const char *str)
{
	int len = 0;
	char *dup_str;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	dup_str = malloc(sizeof(char) * (len + 1));

	if (!dup_str)
		return (NULL);

	for (len++; len--;)
		dup_str[len] = *--str;

	return (dup_str);
}

/**
 * print_string - prints a string(*****Done)
 * @string: the string to be printed
 *
 * Return: None
 */
void print_string(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		_write_char(string[index]);
		index++;
	}
}

/**
 * _write_char - writes the character c to stdout(*****Done)
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_char(char c)
{
	static int idx;
	static char buffer[WRITE_BUF_SIZE];

	if (c == FLUSH_BUFFER || idx >= WRITE_BUF_SIZE)
	{
		write(1, buffer, idx);
		idx = 0;
	}

	if (c != FLUSH_BUFFER)
		buffer[idx++] = c;

	return (1);
}
