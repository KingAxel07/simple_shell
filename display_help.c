#include "shell.h"

/**
 * read_and_print_help - reads a specific help text file and prints it to POSIX stdout
 * @m: copy of environment variables
 * @help_file: name of the help file to read
 * Return: number of characters written, otherwise 0.
 */
ssize_t read_and_print_help(char **m, const char *help_file)
{
	int fd, r, w;
	char *buf;
	char *home, *helpdir;
	size_t letters = 1024;

	buf = malloc((sizeof(char) * letters + 1));
	if (buf == NULL)
		return (0);

	home = _gethome(m);
	helpdir = str_concat(home, help_file);
	fd = open(helpdir, O_RDONLY);
	free(home);

	if (fd == -1)
	{
		free(helpdir);
		free(buf);
		return (0);
	}

	r = read(fd, buf, letters);
	if (r == -1)
	{
		free(helpdir);
		free(buf);
		return (0);
	}

	w = write(STDOUT_FILENO, buf, r);
	if (w == -1)
	{
		free(helpdir);
		free(buf);
		return (0);
	}

	close(fd);
	free(helpdir);
	free(buf);
	return (r);
}

/**
 * read_help - reads the general help text file and prints it to POSIX stdout
 * @m: copy of environment variables
 * Return: number of characters written, otherwise 0.
 */
ssize_t read_help(char **m)
{
	return read_and_print_help(m, "/simple_shell/_helpfiles/help_all.txt");
}

/**
 * read_cdhelp - reads the cd help text file and prints it to POSIX stdout
 * @m: copy of environment variables
 * Return: number of characters written, otherwise 0.
 */
ssize_t read_cdhelp(char **m)
{
	return read_and_print_help(m, "/simple_shell/_helpfiles/help_cd.txt");
}

/**
 * read_exithelp - reads the exit help text file and prints it to POSIX stdout
 * @m: copy of environment variables
 * Return: number of characters written, otherwise 0.
 */
ssize_t read_exithelp(char **m)
{
	return read_and_print_help(m, "/simple_shell/_helpfiles/help_exit.txt");
}

/**
 * read_helphelp - reads the help help text file and prints it to POSIX stdout
 * @m: copy of environment variables
 * Return: number of characters written, otherwise 0.
 */
ssize_t read_helphelp(char **m)
{
	return read_and_print_help(m, "/simple_shell/_helpfiles/help_help.txt");
}
