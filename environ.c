#include "shell.h"

/**
 * _isenv - checks if the input command is "env"
 * @p: array of pointers containing the command and its arguments
 * @myenv: copy of environmental variables
 * Return: -1 if the command is not "env", 0 if it is "env"
 */
int _isenv(char **p, char **myenv)
{
	char target[] = "env";
	int i = 0, j = 0, cont = 0;

	// Find the length of the input command
	while (p[0][j] != '\0')
		j++;

	// Check if the length of the input command matches "env" (3 characters)
	if (j == 3)
	{
		// Compare each character of the input command with "env"
		while (i < 3)
		{
			if (p[0][i] == target[i])
				cont++;
			i++;
		}

		// If all characters match, call _env() and return 0
		if (cont == 3)
		{
			_env(myenv);
			return (0);
		}
	}

	// Return -1 if the command is not "env"
	return (-1);
}

/**
 * create_env - create a copy of the environmental variables
 * @envp: environment variables
 * Return: array of pointers that stores each element of environ variables
 */
char **create_env(char *envp[])
{
	int i, j = 0, c = 0;
	static char **myenv;

	// Count the number of environmental variables
	for (i = 0; envp[i] != NULL; i++)
		;

	// Allocate memory for the copy of the environmental variables
	myenv = _calloc(i + 1, sizeof(char *));
	if (!myenv)
		return (NULL);

	// Copy each environmental variable to the new memory
	while (envp[j] != NULL)
	{
		c = 0;
		// Find the length of the current environmental variable
		while (envp[j][c] != '\0')
			c++;

		// Allocate memory for the current environmental variable in the copy
		myenv[j] = _calloc(c + 1, sizeof(char));
		if (myenv[j] == NULL)
		{
			// Free memory if allocation fails and return NULL
			free_grid(myenv, j);
			return (NULL);
		}

		// Copy the contents of the current environmental variable
		// to the newly allocated memory
		for (i = 0; i < c; i++)
			myenv[j][i] = envp[j][i];

		j++;
	}

	myenv[j] = NULL; // Set the last element to NULL to mark the end of the array
	return (myenv);
}

/**
 * _env - function to print the environment variables
 * @myenv: copy of environmental variables
 * environ points to an array of pointers to strings called the "environment"
 */
void _env(char **myenv)
{
	int i;

	// Loop through the environmental variables and print each one
	for (i = 0; myenv[i] != NULL; i++)
	{
		write(STDOUT_FILENO, myenv[i], _strlen(myenv[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

