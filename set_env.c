#include "shell.h"

/**
 * _issetenv - finds if line input is setenv
 * @p: input of user, array of pointers
 * @myenv: copy of environmental variables
 * @loop: number of loops
 * @e: number of elements in myenv
 * @v: arguments
 * Return: -1 if fails or 0 if success
 */
int _issetenv(char **p, char ***myenv, int *e, int loop, char *v[])
{
	char str[] = "setenv";
	int i = 0, cont = 0, salida = -1;

	i = 0;
	while (p[0][i] != '\0')
	{
		if (i < 6)
		{
			if (p[0][i] == str[i])
				cont++;
		}
		i++;
	}

	if (i == 6)
		cont++;

	if (cont == 7)
	{
		if (p[1] != NULL && p[2] != NULL)
		{
			_setenv(p, myenv, e, loop, v);
		}
		else
		{
			_put_err(p, loop, 5, v);
		}

		salida = 0;
		currentstatus(&salida);
	}
	else if (cont == 6)
	{
		salida = 0;
		_put_err(p, loop, 3, v);
		currentstatus(&salida);
	}

	return (salida);
}

/**
 * _setenv - function to add or modify an environment variable
 * @p: input of user
 * @myenv: copy of environmental
 * @e: number of elements in myenv
 * @loop: number of loops
 * @v: arguments
 */
void _setenv(char **p, char ***mynev, int *e, int loop, char *v[])
	{
	int i, lg, j, k = 0, cont = 0;
	char *entirenv, *withequal;

	lg = _strlen(p[1]);
	withequal = str_concat(p[1], "=");
	entirenv = str_concat(withequal, p[2]);

	for (i = 0; (*myenv)[i] != NULL; i++, cont = 0)
	{
		for (j = 0; p[1][j] != '\0' && j < lg; j++)
		{
			if (p[1][j] == (*myenv)[i][j])
				cont++;
		}

		if (cont == lg)
			break;
	}

	if (cont == lg)
	{
		int p2len = _strlen(p[2]);
		int myenvlen = _strlen((*myenv)[i]);

		if (p2len < myenvlen)
		{
			for (k = 0; entirenv[k] != '\0'; k++)
				(*myenv)[i][k] = entirenv[k];

			for (; k < myenvlen; k++)
				(*myenv)[i][k] = 0;
		}
		else
		{
			(*myenv)[i] = _realloc((*myenv)[i], myenvlen, _strlen(entirenv));
			for (k = 0; entirenv[k] != '\0'; k++)
				(*myenv)[i][k] = entirenv[k];
		}

		free(withequal);
		free(entirenv);
		*e = *e; // This assignment doesn't change anything. It can be omitted.
	}
	else if (cont != lg && p[1] != NULL && p[2] != NULL)
	{
		_setenv_creat(myenv, e, entirenv);
		free(withequal);
		free(entirenv);
	}
	else
	{
		_put_err(p, loop, 5, v);
	}
}

/**
 * _setenv_creat - function to add or modify an environment variable
 * @myenv: copy of environmental
 * @e: number of elements in myenv
 * @entirenv: concatenate arguments
 */
void _setenv_creat(char ***myenv, int *e, char *entirenv)
{
	int i, k;
	char **new_env = NULL;

	new_env = _calloc((*e + 2), sizeof(char *));
	if (!new_env)
		return;

	for (i = 0; (*myenv)[i] != NULL; i++)
	{
		size_t myenvlen = _strlen((*myenv)[i]);
		new_env[i] = _calloc((myenvlen + 1), sizeof(char));
		if (!new_env[i])
		{
			_free_grid(new_env, i);
			return;
		}

		for (k = 0; (*myenv)[i][k] != '\0'; k++)
			new_env[i][k] = (*myenv)[i][k];
	}

	new_env[i] = _strdup(entirenv);
	if (!new_env[i])
	{
		_free_grid(new_env, i);
		return;
	}

	new_env[i + 1] = NULL;
	*e = *e + 1;
	_free_grid(*myenv, *e);
	(*myenv) = new_env;
}
