#include "shell.h"


/**
 * main - Shell skeleton
 * @argc: Number of arguments in the input
 * @argv: Arguments in the input
 * @envp: Environment variables
 * Return: 0 on Success
 */
int main(int argc, char *argv[],char *envp[])
{
	if (argc == 1)
	{
		// Handle case with no arguments
		_no_argv_case(argv, envp);
	}
	else if (argc == 2)
	{
		// Handle case with one argument
		_one_argv_case(argv, envp);
	}
	else
	{
		// Handle cases with more than one argument
		write(STDOUT_FILENO, "NO ADMITTED AMOUNT OF ARGUMENTS\n", 31);
	}

	return (0);
}
