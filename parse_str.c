#include "shell.h"

/**
 * count_occurrences - Counts the occurrences of characters from the lim string
 * in the input string L.
 * @L: The input string
 * @lim: The characters to find inside the L string
 * Return: The number of occurrences found
 */
int count_occurences(char *L,char *lim)
	{
	int num = 0;
	char *ptr;

	while (*lim != '\0')
	{
		ptr = L;
		while (*ptr != '\0')
		{
			if (*ptr != *lim)
			{
				if (*(ptr + 1) == *lim || *(ptr + 1) == '\0')
					num++;
			}
			ptr++;
		}
		lim++;
	}
	return num;
}

/**
 * parsing - Tokenizes the input string based on delimiters " \t\n"
 * @line: Input string to be tokenized
 * Return: An array of pointers to tokens or NULL on failure
 */
char **parsing(char *line)
{
	char *token;
	char **p;
	int buffsize, j = 0;

	if (line == NULL)
		return NULL;

	buffsize = count_occurrences(line, " \t");
	p = _calloc(buffsize + 1, sizeof(char *));
	if (!p)
	{
		perror("No memory");
		return NULL;
	}

	token = _strtoky(line, " \t\n");
	while (token)
	{
		int length = _strlen(token);
		p[j] = _calloc(length + 1, sizeof(char));
		if (!p[j])
		{
			free_grid(p, j);
			perror("No memory");
			return NULL;
		}

		for (int i = 0; i < length; i++)
			p[j][i] = token[i];

		j++;
		token = _strtoky(NULL, " \t\n");
	}
  p[j] = NULL;
  return p;
}
