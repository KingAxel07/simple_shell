#include "shell.h"

/**
 * normal_exit - function to exit the shell normally
 * @m: copy of environmental variables
 * @e: number of elements in m
 */
void normal_exit(char **m, int e)
{
	free_grid(m, e);
	exit(currentstatus(NULL));
}

/**
 * double_ctrl_d_exit - function to exit the shell with double Ctrl+D
 * @m: copy of environmental variables
 * @e: number of elements in m
 * @line: input of user
 */
void double_ctrl_d_exit(char **m, int e, char *line)
{
	free(line);
	free_grid(m, e);
	write(STDIN_FILENO, "#cisfun$ ", 9);
	write(STDIN_FILENO, "\n", 1);
	exit(currentstatus(NULL));
}

/**
 * normal_exit_with_newline - function to exit the shell normally with newline
 * @m: copy of environmental variables
 * @e: number of elements in m
 */
void normal_exit_with_newline(char **m, int e)
{
	free_grid(m, e);
	write(STDIN_FILENO, "\n", 1);
	exit(currentstatus(NULL));
}

/**
 * _getline_shell - function to read what the user writes
 * @loop_counter: pointer to loop counter
 * @env_length: length of m (environmental variables)
 * @env: copy of environmental variables
 * Return: line in success, otherwise NULL.
 */
char *_getline_shell(int *loop_counter, char **env, int env_length)
{
	char letter[1] = {0}, *line = NULL;
	size_t bufsize = 0;
	static int num = 1;

	if (num == 2)
		double_ctrl_d_exit(env, env_length, line);

	for (; (num != 0); bufsize = 0, free(line))
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);
		*loop_counter = *loop_counter + 1;
		signal(SIGINT, _signal_handler);

		while ((num = read(STDIN_FILENO, letter, 1)) > 0)
		{
			if (bufsize == 0)
				line = _calloc(bufsize + 3, sizeof(char));
			else
				line = _realloc(line, bufsize, bufsize + 3);
			if (!line)
			{
				num = 0;
				break;
			}
			line[bufsize] = letter[0];
			line[bufsize + 1] = '\n';
			line[bufsize + 2] = '\0';

			if (line[bufsize] == '\n')
				break;

			bufsize++;
		}

		if (num == 0 && bufsize == 0)
			break;
		else if (num == 0 && bufsize != 0)
		{
			num = 2;
			break;
		}
		else if (line[0] != '\n')
			return (line);
	}

	if (num == 0)
		normal_exit_with_newline(env, env_length);

	return (line);
}

/**
 * _getline_with_file - function to read from a file
 * @loop_counter: pointer to loop counter
 * @env_length: length of m (environmental variables)
 * @env: copy of environmental variables
 * @av: arguments in input
 * Return: line in success, otherwise NULL.
 */
char *_getline_with_file(int *loop_counter, char **env, int env_length, char **av)
{
	char letter[1] = {0}, *line = NULL;
	size_t bufsize = 0;
	static unsigned int num = 1;
	static int fd;

	for (; (num != 0); bufsize = 0, free(line))
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			free_grid(env, env_length);
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": 0: Can't open ", 16);
			write(STDERR_FILENO, av[1], _strlen(av[1]));
			write(STDERR_FILENO, "\n", 1);
			exit(127);
		}

		*loop_counter = *loop_counter + 1;
		while ((num = read(fd, letter, 1)) > 0)
		{
			if (bufsize == 0)
				line = _calloc(bufsize + 3, sizeof(char));
			else
				line = _realloc(line, bufsize, bufsize + 3);
			if (!line)
			{
				num = 0;
				break;
			}
			line[bufsize] = letter[0];
			line[bufsize + 1] = '\n';
			line[bufsize + 2] = '\0';
			bufsize++;
		}

		if (num == 0 && bufsize == 0)
			break;
		else if (line[0] != '\n')
			return (line);
	}

	if (num == 0)
	{
		close(fd);
		salida3(env, env_length);
	}

	return (line);
}

