#include "shell.h"
#define BUF_SIZE 2048

/**
 * check_cd_builtin - checks if the input is a "cd" builtin command
 * @args: input of user, array of pointers
 * @loop: counter of loop
 * @argv: arguments in input
 * @env: copy of environment variables
 * Return: -1 if not a "cd" command, 0 if it is a "cd" command
 */
int check_cd_builtin(char **args, int loop, char *argv[], char **env)
{
	char command[] = "cd";
	int i = 0, count = 0, value = -1;

	while (args[0][i] != '\0')
	{
		if (i < 2)
		{
			if (args[0][i] == command[i])
				count++;
		}
		i++;
	}
	if (i == 2)
		count++;

	if (count == 3)
	{
		change_directory(args, loop, argv, env);
		value = 0;
	}
	else if (count == 2)
	{
		print_error(args, loop, 3, argv);
		value = 0;
	}
	return (value);
}

/**
 * clean_buffer - clean the buffer
 * @buffer: pointer to the buffer
 * Return: None
 */
void clean_buffer(char *buffer)
{
	int i;

	for (i = 0; i < BUF_SIZE; i++)
		buffer[i] = 0;
}

/**
 * fill_buffer - fill the buffer with data
 * @buffer: pointer to the buffer
 * @aux: pointer to aux data
 * Return: None
 */
void fill_buffer(char *buffer, char *aux)
{
	int w;

	for (w = 0; aux[w] != '\0'; w++)
		buffer[w] = aux[w];
	for (; w < BUF_SIZE; w++)
		buffer[w] = 0;
}

/**
 * change_directory - Changes the current directory of the process.
 * @args: input of user, array of pointers
 * @loop: loops counter
 * @argv: arguments in input
 * @env: copy of environment variables
 * Return: None
 */
void change_directory(char **args, int loop, char *argv[], char **env)
{
	int value = 0, z = 0;
	static char buffer[BUF_SIZE];
	static int count = 1;
	char *home, aux[BUF_SIZE] = {0};

	currentstatus(&z);
	if (count == 1)
	{
		home = _gethome(env);
		if (!home)
			getcwd(home, BUF_SIZE);
		_update_oldpwd(getcwd(buffer, BUF_SIZE), env);
		fill_buffer(buffer, _gethome(env));
		count++;
	}
	if (args[1] == NULL)
	{
		clean_buffer(buffer);
		getcwd(buffer, BUF_SIZE);
		_update_oldpwd(buffer, env);
		value = chdir((const char *)_gethome(env));
		_update_pwd(_gethome(env), env);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		clean_buffer(aux);
		getcwd(aux, BUF_SIZE);
		_update_oldpwd(aux, env);
		write(STDOUT_FILENO, buffer, BUF_SIZE);
		write(STDOUT_FILENO, "\n", 1);
		value = chdir((const char *) buffer);
		_update_pwd(buffer, env);
		fill_buffer(buffer, aux);
	}
	else
	{
		clean_buffer(buffer);
		getcwd(buffer, BUF_SIZE);
		_update_oldpwd(buffer, env);
		value = chdir((const char *)args[1]);
		_update_pwd(args[1], env);
	}
	if (value == -1)
		print_error(args, loop, 1, argv);
}
