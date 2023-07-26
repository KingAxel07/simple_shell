#include "shell.h"

/**
 * print_number - Prints an integer to the standard error output
 * @n: The integer to be printed
 * Return: Always void (no return value)
 */
void print_number(int n)

	{
	unsigned int num, count = 1, divisor = 1;

	if (n < 0)
	{
		write(STDERR_FILENO, "-", 1);
		num = -n;
	}
	else
	{
		num = n;
	}

	while (num / divisor > 9)
	{
		divisor *= 10;
		count++;
	}

	for (; count > 0; count--)
	{
		char digit = '0' + (num / divisor);
		write(STDERR_FILENO, &digit, 1);
		num %= divisor;
		divisor /= 10;
	}
}
