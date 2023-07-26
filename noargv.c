#include "shell.h"

/**
 * handle_commands - Handles the different commands like env, cd, exit, help,
 *                   unsetenv, and setenv.
 * @args: Array of pointers to the command and its arguments.
 * @loop: Number of loops.
 * @line: Input command line.
 * @argv: Command line arguments.
 * @env: Copy of the environment variables.
 * @env_count: Number of elements in env.
 * @full_input: Complete input string.
 */
void handle_commands(char **args, int loop,char *line,char *line, char *argv[],char ***env,int *env_count, char *full_input)
	{
	int value;

	line = remove_comments(line);
	args = parsing(line);
	if (args)
	{
		int i;
		for (i = 0; args[i] != NULL; i++)
			;
		value = rev(args, loop, line, argv, env, env_count, full_input);
		if (value != 0)
		{
			args = check_binary(args, *env);
			if (args)
				execute_command(args, line, i, loop, argv, *env_count, *env, full_input);
		}
		free_grid(args, i);
		free(line);
	}
	else
	{
		free(line);
		fflush(STDIN_FILENO);
	}
	_put_err(args, loop, 0, argv);
}

/**
 * shell_no_argv - Initializes the shell without filename at input.
 * @argv: Arguments in the input.
 * @envp: Environment variables.
 */
void shell_no_argv(char *argv[], char *envp[])
{
	char *line = NULL, **env = NULL, *p = NULL, *pr1 = NULL;
	int env_count = 0, semicolon_flag = 0;
	static int loop;

	loop = 0;
	while (1)
	{
		if (loop == 0)
		{
			env = create_env(envp);
			for (env_count = 0; env[env_count] != NULL; env_count++)
				;
		}
		line = _getline(&loop, env, env_count);
		semicolon_flag = handle_semicolons(line, loop, argv);
		if (!(semicolon_flag == 1))
		{
			p = _strtoky2(line, ";\n");
			while (p)
			{
				pr1 = _calloc(_strlen(p) + 2, sizeof(char));
				for (int i = 0; p[i] != '\0'; i++)
					pr1[i] = p[i];
				pr1[i] = '\n';
				pr1[i + 1] = '\0';
				handle_commands(pr1, loop, argv, &env, &env_count, line);
				p = _strtoky2(NULL, ";\n");
			}
		}
		free(line);
	}
}
