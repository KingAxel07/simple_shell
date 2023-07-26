#include "shell.h"


/**
 * shell_yes_argv - Shell form with command line arguments.
 * @argv: Arguments in the input.
 * @envp: Environment variables.
 */
void shell_yes_argv(char *argv[], char *envp[])
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
		line = _getlineav(&loop, env, env_count, argv);
		semicolon_flag = handle_semicolons(line, loop, argv);
		if (!(semicolon_flag == 1))
		{
			p = _strtoky2(line, ";\n");
			while (p)
			{
				pr1 = _calloc(_strlen(p) + 2, sizeof(char));
				int i;
				for (i = 0; p[i] != '\0'; i++)
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
