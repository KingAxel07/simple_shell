#include "shell.h"

/**
 * sigint_handler - Handle SIGINT signal (Ctrl+C)
 * @signum: The signal number (unused)
 */
void sigint_handler(int signum)
{
	(void)signum;//to avoid unsed parameter warning

	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}
