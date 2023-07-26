#include "shell.h"

/**
 * _verifypath - check if the path has a : at the beginning
 * or if it contains consecutive colons ::, and fix the path if needed.
 * @path: the PATH string to verify
 * @pwd: the string inside PWD env variable
 * Return: the verified and fixed path
 */
char *_verifypath(char *path, char *pwd)
{
	int a = 0, c = 0, i = 0;
	char *newpath = NULL;

	while (path[c] != '\0')
		c++;

	while (path[a] != '\0')
	{
		if (path[0] == ':')
		{
			newpath = _calloc(c + 1, sizeof(char));
			newpath[0] = pwd[0];
			for (i = 0; path[i] != '\0'; i++)
				newpath[i + 1] = path[i];
			free(path);
			path = newpath;
			a++;
			c++;
		}
		else if (path[a] == ':' && path[a + 1] == ':')
		{
			newpath = _calloc(c + 1, sizeof(char));
			for (i = 0; i <= a; i++)
				newpath[i] = path[i];
			newpath[i] = pwd[0];
			for (i = i + 1; path[i] != '\0'; i++)
				newpath[i] = path[i - 1];
			free(path);
			a++;
			path = newpath;
		}
		a++;
	}

	return (path);
}

/**
 * _getpath - get the string in PATH env
 * @env: environment variables
 * Return: string inside PATH env variable
 */
char *_getpath(char **env)
{
	int i, j, k = 0, w = 0, cont = 0;
	char str[] = "PATH=";
	char *path;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; env[i][j] != '\0'; j++)
		{
			if (cont == 5)
				break;
			if (env[i][j] == str[j])
				cont++;
			else
				break;
		}
		if (cont == 5)
			break;
	}

	if (cont == 5)
	{
		k = 5;
		while (env[i][k] != '\0')
		{
			w++;
			k++;
		}

		if (w == 0)
			return (NULL);

		path = _calloc(w + 1, sizeof(char));
		if (path == NULL)
			return (NULL);

		k = 5;
		while (env[i][k] != '\0')
		{
			path[k - 5] = env[i][k];
			k++;
		}

		return (path);
	}

	return (NULL);
}

/**
 * checkbin - checks if arg[0] contains /bin/ in its PATH
 * @args: input of user, array of pointers to arguments
 * @env: copy of environment variables
 * Return: modified array of arguments.
 */
char **checkbin(char **args, char **env)
{
	unsigned int i = 0, j = 0, k = 0;
	struct stat veri;
	char *path, *tokens, *buf, *newpath;
	char *full_path;

	if (args == NULL || args[0] == NULL || _strlen(args[0]) == 0)
		return (NULL);

	i = _strlen(args[0]);
	path = _getpath(env);
	if (path == NULL)
		return (args);

	newpath = _verifypath(path, ".");
	tokens = _strtoky(newpath, ":");

	if (!tokens)
		return (NULL);

	while (tokens != NULL)
	{
		while (tokens[j] != '\0')
			j++;

		buf = _calloc(j + 2, sizeof(char));
		if (buf == NULL)
			perror("No memory");

		for (k = 0; k < j; k++)
			buf[k] = tokens[k];

		buf[k] = '/';
		full_path = str_concat(buf, args[0]);

		if (stat(full_path, &veri) == 0)
		{
			args[0] = _realloc2(buf, args[0], i, _strlen(full_path));
			free(buf), free(full_path);
			free(newpath);
			return (args);
		}

		tokens = _strtoky(NULL, ":");
		j = 0;
		free(buf), free(full_path);
	}

	free(newpath);
	return (args);
}

