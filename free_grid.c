#include "shell.h"

/**
 * free_2d_array - free a dynamically allocated 2D array (matrix)
 * @matrix: The matrix to be freed
 * @rows: The number of rows in the matrix
 * Return: Nothing
 */
void free_2d_array(char **matrix, int rows)
{
	int i;

	for (i = 0; i < rows; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

