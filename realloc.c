#include "shell.h"

/**
 * _realloc - Change the size and copy the content of a memory block
 * @ptr: Malloc pointer to reallocate
 * @old_size: Old number of bytes
 * @new_size: New number of bytes
 * Return: Pointer to the reallocated memory block or NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
	{
	char *p = NULL;

	if (new_size == old_size)
		return ptr;

	if (ptr == NULL)
	{
		p = _calloc(new_size, sizeof(char));
		return p;
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return NULL;
	}

	p = _calloc(new_size, sizeof(char));
	if (!p)
	{
		free(ptr);
		return NULL;
	}

	size_t min_size = old_size < new_size ? old_size : new_size;
	for (size_t i = 0; i < min_size; i++)
		p[i] = ((char *)ptr)[i];

	free(ptr);
	return p;
}

/**
 * _realloc2 - Change the size and copy the content of a memory block
 * @a: String to add
 * @p: Malloc pointer to reallocate
 * @old: Old number of bytes
 * @new_size: New number of bytes
 * Return: Pointer to the reallocated memory block or NULL on failure
 */
void *_realloc2(char *a, char *p, size_t old, size_t new_size)
{
	char *pa = NULL;
	size_t j = 0;

	if (new_size == old)
		return p;

	if (p == NULL || a == NULL)
	{
		pa = _calloc(new_size, sizeof(char));
		return pa;
	}

	while (a[j] != '\0')
		j++;

	if (new_size == 0 && p != NULL)
	{
		free(p);
		return NULL;
	}

	pa = _calloc(new_size, sizeof(char));
	if (!pa)
	{
		free(p);
		return NULL;
	}

	size_t min_size = j < new_size ? j : new_size;
	for (size_t i = 0; i < min_size; i++)
		pa[i] = a[i];

	min_size = old < new_size ? old : new_size;
	for (size_t i = j, k = 0; i < min_size; i++, k++)
		pa[i] = p[k];

	free(p);
	return pa;
}
