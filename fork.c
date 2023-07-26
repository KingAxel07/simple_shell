#include "shell.h"

static int current_status; // Global variable to store the current status

/**
 * get_current_status - get the current status
 * @status: pointer to the value inside wait
 * Return: the actual changed status
 */
int get_current_status(int *status)
{
	static int actual_status;

	if (status)
		actual_status = *status;
	return (actual_status);
}

/**
 * _fork_and_execute - creates a process and executes the command
 * @args: array of pointers (arguments)
 * @input: input typed by the user
 * @args_count: count of arguments
 * @loop_count: count of loops
 * @command_args: arguments in input
 * @env_length: length of the environmental variables
 * @env_copy: copy of environmental variables
 * @full_input: complete input
 * Return: Nothing.
 */
void _fork_and_execute(char **args, char *input, int args_count, int loop_count,
					   char **command_args, int env_length, char **env_copy, char *full_input)
{
	pid_t child_pid;
	int exist, execute;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		exit(127);
	}
	if (child_pid == 0)
	{
		if (execve(args[0], args, env_copy) == -1)
		{
			exist = access((const char *) args[0], F_OK);
			execute = access((const char *) args[0], X_OK);
			if (exist == 0 && execute == -1)
			{
				_put_error(args, loop_count, 4, command_args);
				free(full_input), free(input);
				free_grid(args, args_count), free_grid(env_copy, env_length);
				exit(126);
			}
			else
			{
				_put_error(args, loop_count, 3, command_args);
			}
			free(full_input), free(input);
			free_grid(args, args_count), free_grid(env_copy, env_length);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			get_current_status(&exit_status);
		}
	}
}

