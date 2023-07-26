#include "shell.h"


/**
 * _put_err - writes the error message to stderr
 * @p: input pointer 
 * @loop: counter of loops 
 * @sig: signal 
 * @v: aguments in input 
 * Return: Nothing.
 */
void _put_err(char **p, int loop, int sig, char *v[])
{
	static int pr = 1;
	if (sig == 0)
		pr = 0;
	pr++;

	if (sig >= 3 && sig <= 5)
		pr = sig;
	if (pr >= 2 && pr <= 5)
	{
		write (STDERR_FILENO, v[0], _strlen(v[0]));
		write(STDERR_FILENO, ": ",2);
		print_number(loop);
		write(STDERR_FILENO, ": ",2);
	}


	switch (pr)
	{
		case 2;
		_builtinerr(p);
		break;
		case 3;
		if (sig ==3)
		{
		
			_errorgarbage(p);
			pr =1;
		}
		break;
		case 4:
		if (sig == 4)
		{
			 write(STDERR_FILENO,p[0],_strlen(p[0]));
			 write(STDERR_FILENO, ": Permission denied\n", 20);
		}
		break;
		case 5:
            if (sig == 5)
                _builtinerr2(p);
            break;
    }
}

/**
 * _builtinerr - writes specific built-in command error message to stderr
 * @p: input pointer
 * Return: Nothing.
 */
void _builtinerr(char **p)
{
    char *builtins[] = {"cd", "exit", "help"};
    int i, j;

    for (i = 0; i < 3; i++)
    {
        j = 0;
        while (p[0][j] != '\0' && p[0][j] == builtins[i][j])
            j++;

        if (p[0][j] == '\0' && builtins[i][j] == '\0')
        {
            switch (i)
            {
                case 0:
                    _errorcd(p);
                    break;
                case 1:
                    _errorexit(p);
                    break;
                case 2:
                    _errorhelp(p);
                    break;
            }
            break;
        }
    }
}

/**
 * _builtinerr2 - writes specific built-in command error message to stderr
 * @p: input pointer
 * Return: Nothing.
 */
void _builtinerr2(char **p)
{
    char *builtins[] = {"unsetenv", "setenv"};
    int i, j;

    for (i = 0; i < 2; i++)
    {
        j = 0;
        while (p[0][j] != '\0' && p[0][j] == builtins[i][j])
            j++;

        if (p[0][j] == '\0' && builtins[i][j] == '\0')
        {
            _errorenv(p);
            break;
        }
    }
}
