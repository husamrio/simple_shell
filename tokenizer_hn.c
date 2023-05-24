#include "shell.h"

/**
 * split_string - splits a string into words and (*****Done)
 * repeated delimiters are ignored.
 * @str: Input string.
 * @delim: the delimiter for the string
 * Return: array of strings pointer, or NULL on failure
 */

char **split_string(char *str, char *delim)
{
	int c, b, k, h, num_words = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (c = 0; str[c] != '\0'; c++)
		if (!isChDel(str[c], delim) && (isChDel(str[c + 1], delim) || !str[c + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (c = 0, b = 0; b < num_words; b++)
	{
		while (isChDel(str[c], delim))
			c++;
		k = 0;
		while (!isChDel(str[c + k], delim) && str[c + k])
			k++;
		result[b] = malloc((k + 1) * sizeof(char));
		if (!result[b])
		{
			for (k = 0; k < b; k++)
				free(result[k]);
			free(result);
			return (NULL);
		}
		for (h = 0; h < k; h++)
			result[b][h] = str[c++];
		result[b][h] = 0;
	}
	result[b] = NULL;
	return (result);
}


/**
* my_split_string - splits string into words(*****Done)
* @str: Input string
* @delim: the delimiter character
* Return: an array of strings pointer, or NULL on failure
*/
char **my_split_string(char *str, char delim)
{
int c, b, k, h, num_words = 0;
char **result;

if (str == NULL || str[0] == '\0')
return (NULL);

for (c = 0; str[c] != '\0'; c++)
if ((str[c] != delim && str[c + 1] == delim) ||
(str[c] != delim && !str[c + 1]) || str[c + 1] == delim)
num_words++;

if (num_words == 0)
return (NULL);

result = malloc((1 + num_words) *sizeof(char *));
if (!result)
return (NULL);

for (c = 0, b = 0; b < num_words; b++)
{
while (str[c] == delim && str[c] != delim)
c++;
k = 0;
while (str[c + k] != delim && str[c + k] && str[c + k] != delim)
k++;
result[b] = malloc((k + 1) * sizeof(char));
if (!result[b])
{
for (k = 0; k < b; k++)
free(result[k]);
free(result);
return (NULL);
}
for (h = 0; h < k; h++)
result[b][h] = str[c++];
result[b][h] = 0;
}
result[b] = (NULL);
return (result);
}

