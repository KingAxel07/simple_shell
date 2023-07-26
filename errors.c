#include "shell.h"

/**
 * print_error_cd - writes an error message for cd command
 * @command: The name of the command (cd)
 * @directory: The directory that couldn't be changed to
 * Return: nothing.
 */
void print_error_cd(char *command, char *directory)
{
	int status = 2;

	write(STDERR_FILENO, command, 2);
	write(STDERR_FILENO, ": can't cd to ", 14);
	write(STDERR_FILENO, directory, _strlen(directory));
	write(STDERR_FILENO, "\n", 1);
	update_status(&status);
}

/**
 * print_error_exit - writes an error message for exit command
 * @command: The name of the command (exit)
 * @argument: The invalid argument given to exit
 * Return: nothing.
 */
void print_error_exit(char *command, char *argument)
{
	int status = 2;

	write(STDERR_FILENO, command, 4);
	write(STDERR_FILENO, ": Illegal number: ", 18);
	write(STDERR_FILENO, argument, _strlen(argument));
	write(STDERR_FILENO, "\n", 1);
	update_status(&status);
}

/**
 * print_error_help - writes an error message for help command
 * @command: The name of the command (help)
 * @topic: The help topic that couldn't be found
 * Return: nothing.
 */
void print_error_help(char *command, char *topic)
{
	int status = 2;

	write(STDERR_FILENO, command, 4);
	write(STDERR_FILENO, ": no help topics match '", 24);
	write(STDERR_FILENO, topic, _strlen(topic));
	write(STDERR_FILENO, "'. Try 'help help' or 'man -k '", 31);
	write(STDERR_FILENO, topic, _strlen(topic));
	write(STDERR_FILENO, "' or info '", 11);
	write(STDERR_FILENO, topic, _strlen(topic));
	write(STDERR_FILENO, "'\n", 2);
	update_status(&status);
}

/**
 * print_error_not_found - writes an error message for unknown commands
 * @command: The name of the command that was not found
 * Return: nothing.
 */
void print_error_not_found(char *command)
{
	int status = 2;

	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
	update_status(&status);
}

/**
 * print_error_env - writes an error message for environment variable operations
 * @command: The name of the command (setenv or unsetenv)
 * Return: nothing.
 */
void print_error_env(char *command)
{
	int status = 2;

	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": unable to add/rm variable\n", 28);
	update_status(&status);
}
