#include "shell.h"

/**
 * free_ptr - Frees a pointer & sets it to NULL.(***Done)
 * @ptr: Address of the pointer to be freed.
 *
 * Returns: 1 if released, otherwise 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
