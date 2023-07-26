#include "shell.h"

/**
 * _is_help_builtin - Checks if args[0] is a built-in command for help.
 * @p: Input pointer.
 * @loop: Counter of loops.
 * @v: Arguments in input.
 * @m: Copy of environment variables.
 * Return: 0 if the help exists or -1 if not.
 */
int _is_help_builtin(char **p, int loop, char *v[], char **m)
{
	char *help_commands[] = {"cd", "exit", "help"};
	int i, num_commands = sizeof(help_commands) / sizeof(help_commands[0]);
	int is_help_command = 0, salida = -1;

	for (i = 0; i < num_commands; i++)
	{
		if (strcmp(p[0], help_commands[i]) == 0)
		{
			is_help_command = 1;
			break;
		}
	}

	if (is_help_command)
	{
		_help_builtin(p, loop, v, m);
		salida = 0;
	}

	return (salida);
}

/**
 * _help_builtin - Displays help for built-in commands.
 * @p: Input pointer.
 * @loop: Counter of loops.
 * @v: Arguments in input.
 * @m: Copy of environment variables.
 * Return: Nothing.
 */
void _help_builtin(char **p, int loop, char *v[], char **m)
{
	if (strcmp(p[1], "cd") == 0)
		read_cdhelp(m);
	else if (strcmp(p[1], "exit") == 0)
		read_exithelp(m);
	else if (strcmp(p[1], "help") == 0)
		read_helphelp(m);
	else
		_put_err(p, loop, 1, v);
}

/**
 * _help - Writes help information based on the input.
 * @p: Input pointer.
 * @loop: Counter of loops.
 * @v: Arguments in input.
 * @m: Copy of environment variables.
 * Return: Nothing.
 */
void _help(char **p, int loop, char *v[], char **m)
{
	if (p[0] != NULL && p[1] == NULL)
		read_help(m);
	else
		_is_help_builtin(p, loop, v, m);
}
