#include <stdlib.h>
#include "shell.h"

/**
 * _calloc - allocates memory for an array of elements, each with a given size
 * @nmemb: number of elements to allocate memory for
 * @size: the size of each element in bytes
 * Return: pointer to the allocated memory, or NULL if failure
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
    if (nmemb == 0 || size == 0)
    {
        return NULL;
    }

    void *p = malloc(nmemb * size);
    if (p == NULL)
    {
        return NULL;
    }

    // Initialize the allocated memory to zero
    unsigned char *byte_ptr = p;
    for (unsigned int i = 0; i < nmemb * size; i++)
    {
        byte_ptr[i] = 0;
    }

    return p;
}

