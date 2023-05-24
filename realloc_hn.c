#include "shell.h"

/**
 * _my_memset - Fills memory with constant byte(*****Done)
 * @ptr: Memory area pointer
 * @value: Byte value to fill *ptr with
 * @num: Number of bytes to be filled
 *
 * Return: Pointer to the memory area `ptr`
 */
char *_my_memset(char *ptr, char value, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		ptr[i] = value;

	return (ptr);
}

/**
 * free_string_array - frees a string of string arrays(***Done)
 * @str_array: string array to be freed
 */
void free_string_array(char **str_array)
{
	char **temp = str_array;

	if (!str_array)
		return;

	while (*str_array)
		free(*str_array++);

	free(temp);
}

/**
 * realloc_block - Reallocates a block of memory(***Done)
 * @prev_ptr: Pointer to the previous allocated block
 * @prev_s: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the reallocated block
 */
void *realloc_block(void *prev_ptr, unsigned int prev_s, unsigned int new_size)
{
	char *new_ptr;

	if (!prev_ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(prev_ptr);
		return (NULL);
	}
	if (new_size == prev_s)
		return (prev_ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	prev_s = prev_s < new_size ? prev_s : new_size;
	while (prev_s--)
		new_ptr[prev_s] = ((char *)prev_ptr)[prev_s];
	free(prev_ptr);
	return (new_ptr);
}
