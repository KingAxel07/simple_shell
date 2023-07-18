#include "shell.h"

/**
 * _atoi - converts string characters to integers.
 * @s: pointer to the input string.
 *
 * Return: the converted integer value.
 */
int _atoi(char *s)
{
	unsigned int len = 0, i, start, end, num = 0, size;
	int sign = 1;

	while (s[len] != '\0')
		len++;

	for (start = 0; start < len; start++)
	{
		if (s[start] >= '0' && s[start] <= '9')
			break;
	}

	for (end = start; end < len; end++)
	{
		if (!(s[end] >= '0' && s[end] <= '9'))
			break;
	}

	for (i = 0; i < start; i++)
	{
		if (s[i] == '-')
			sign = sign * (-1);
	}

	size = end - start;
	while (size >= 1)
	{
		num = (num * 10) + (s[start] - '0');
		start++;
		size--;
	}

	num = num * sign;
	return (num);
}

