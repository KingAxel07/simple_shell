#include "shell.h"

/**
 * get_home_directory - function to get the value of the `HOME` environment variable
 * @env: copy of environment variables
 * Return: The string inside the `HOME` environment variable
 */
char *get_home_directory(char **env)
{
	int i, j, k, cont = 0;
	char search_str[] = "HOME=";
	char *home_dir = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; env[i][j] != '\0'; j++)
		{
			if (cont == 5)
				break;
			if (env[i][j] == search_str[j])
				cont++;
			else
				break;
		}
		if (cont == 5)
			break;
	}
	if (cont == 5)
	{
		home_dir = env[i];
		for (k = 0; k < 5; k++)
		{
			home_dir++;
		}
	}
	return (home_dir);
}

