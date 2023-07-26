#include "shell.h"

/**
 * _strchr - search if a character is inside a string
 * @s: string to search
 * @c: character to find
 * Return: 1 if found, 0 if not
 */
int _strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return 1;
		s++;
	}
	return 0;
}

/**
 * _strtoky - tokenize the input string using the given delimiters
 * @s: string to cut into parts
 * @delimiters: delimiters
 * Return: first partition
 */
char *_strtoky(char *s, const char *delimiters)
{
	static char *last;
	int i = 0, j = 0;

	if (!s)
		s = last;

	while (s[i] != '\0')
	{
		if (!_strchr(delimiters, s[i]) && s[i + 1] == '\0')
		{
			last = s + i + 1;
			*last = '\0';
			s = s + j;
			return s;
		}
		else if (!_strchr(delimiters, s[i]) && !_strchr(delimiters, s[i + 1]))
			i++;
		else if (!_strchr(delimiters, s[i]) && _strchr(delimiters, s[i + 1]))
		{
			last = s + i + 1;
			*last = '\0';
			last++;
			s = s + j;
			return s;
		}
		else if (_strchr(delimiters, s[i]))
		{
			j++;
			i++;
		}
	}

	return NULL;
}
/**
 * _strtoky2 - tokenize the input string using a specific delimiter
 * @s: string to cut into parts
 * @delimiter: delimiter
 * Return: first partition
 */
char *_strtoky2(char *s, char delimiter)
{
	static char *last;
	int i = 0, j = 0;

	if (!s)
		s = last;

	while (s[i] != '\0')
	{
		if (s[i] != delimiter && s[i + 1] == '\0')
			i++;
		else if (s[i] != delimiter && s[i + 1] != delimiter)
			i++;
		else if (s[i] != delimiter && s[i + 1] == delimiter)
		{
			last = s + i + 1;
			*last = '\0';
			last++;
			s = s + j;
			return s;
		}
		else if (s[i] == delimiter)
		{
			j++;
			i++;

		}
	}
	return NULL;
}
