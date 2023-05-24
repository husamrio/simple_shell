#include "shell.h"

/**
 * betty_strncpy - Copies a string up to a specified length.(*****Done)
 * @dest: The destination string.
 * @src: The source of string.
 * @n: The number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *betty_strncpy(char *dest, char *src, int n)
{
	int i, k;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}

	return (s);
}
/**
 * string_nconcat - concatenates two strings using limited bytes(***Done)
 * @dest: pointer to the 1st string
 * @src: pointer to the 2nd string
 * @n: maximum n0. of bytes to be used from src
 *
 * Return: pointer to the concatenated string
 */
char *string_nconcat(char *dest, char *src, int n)
{
	int a = 0, b = 0;
	char *result = dest;

	while (dest[a] != '\0')
		a++;

	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}

	if (b < n)
		dest[a] = '\0';

	return (result);
}


/**
* find_character - Locates a char in a string.(***Done)
* @str: The string to be searched.
* @ch: The character to be looked found.

* Return: A pointer to the memory area containing the character, or
* NULL if not found.
*/
char *find_character(char *str, char ch)
{
do {
if (*str == ch)
return (str);
} while (*str++ != '\0');

return (NULL);
}

