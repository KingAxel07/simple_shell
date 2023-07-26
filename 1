#include "shell.h"
#include <limits.h>

/**
 * process_exit_command - process the "exit" command and terminate the shell
 * @args: input user, array of pointers
 * @loop: loop counter
 * @input: input user
 * @num_args: number of pointers inside the array of pointers
 * @argv: arguments in input
 * @env: copy of environmental variables
 * @env_elements: number of elements in env
 * @full_input: complete input
 */
void process_exit_command(char **args, int loop, char *input, int num_args, char **argv, char **env, int env_elements, char *full_input)
{
	unsigned int count = 0, flag = 0;
	long int value = 0;

	if (args[1] == NULL || (args[1][0] == '0' && args[1][1] == '\0'))
	{
		free(input), free(full_input), free_grid(args, num_args), free_grid(env, env_elements);
		exit(currentstatus(NULL));
	}
	else
	{
		while (args[1][count] != '\0')
		{
			if ((args[1][0] != '+' && args[1][0] != '-') &&
			    (args[1][count] < 48 || args[1][count] > 57))
			{
				flag = 1;
				break;
			}
			count++;
		}
		if (flag == 1)
			print_error(args, loop, 1, argv);
		else
		{
			value = _atoi(args[1]);
			if (!(value > INT_MAX) && value > 0)
			{
				value = value % 256;
				free(input), free(full_input), free_grid(args, num_args);
				free_grid(env, env_elements), exit(value);
			}
			else if (value < 0)
			{
				print_error(args, loop, 1, argv);
				free(input), free(full_input), free_grid(args, num_args);
				free_grid(env, env_elements), exit(2);
			}
			else
				print_error(args, loop, 1, argv);
		}
	}
}

/**
 * check_exit_builtin - checks if the input is an "exit" builtin command
 * @args: input of user, array of pointers
 * @loop: loop counter
 * @input: input user
 * @argv: arguments in input
 * @env: copy of environmental variables
 * @full_input: complete input
 * Return: -1 if there is no "exit" command, 0 if there is the "exit" command
 */
int check_exit_builtin(char **args, int loop, char *input, char **argv, char **env, char *full_input)
{
	char command[] = "exit";
	int i, count = 0, exit_flag = -1, num_args = 0, env_elements = 0;

	for (num_args = 0; args[num_args] != NULL; num_args++)
		;
	for (env_elements = 0; env[env_elements] != NULL; env_elements++)
		;

	i = 0;
	while (args[0][i] != '\0')
	{
		if (i < 4)
		{
			if (args[0][i] == command[i])
				count++;
		}
		i++;
	}
	if (i == 4)
		count++;

	if (count == 5)
	{
		process_exit_command(args, loop, input, num_args, argv, env, env_elements, full_input);
		exit_flag = 0;
	}
	else if (count == 4)
	{
		exit_flag = 0;
		print_error(args, loop, 3, argv);
	}
	return (exit_flag);
}

