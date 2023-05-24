#include "shell.h"

/**
 * str_len - Returns length of string.(***Done)
 * @str: The string length to check.
 *
 * Return: Integer len of string.
 */
int str_len(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * betty_strcmp - Performs lexicographic comparison of two strings.(*Done)
 * @str1: The 1st string.
 * @str2: The 2nd string.
 *
 * Return: Neg if str1 < str2, pos if str1 > str2, 0 if str1 == str2.
 */
int betty_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _startsWith - Checks if string starts with another string.(*Done)
 * @haystack: The string to search for.
 * @needle: The prefix to find.
 *
 * Return: Address of the next character of `haystack` if it
 * starts with `needle`, otherwise NULL.
 */
char *_startsWith(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}
	return ((char *)haystack);
}


/**
 * betty_str_concat -Two strings concatenates(*Done)
 * @dest: Buffer destination
 * @src: source buffer
 *
 * Return: destination buffer pointer
 */
char *betty_str_concat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
