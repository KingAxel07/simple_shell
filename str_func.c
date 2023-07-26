#include "shell.h"

/**
 * str_concat - concatenate two strings into a new string
 * @s1: first string
 * @s2: second string
 * Return: pointer to the concatenated string or NULL on failure
 */
char *str_concat(const char *s1, const char *s2)
{
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	size_t len1 = _strlen(s1);
	size_t len2 = _strlen(s2);

	char *result = _calloc(len1 + len2 + 1, sizeof(char));
	if (result == NULL)
		return NULL;

	for (size_t i = 0; i < len1; i++)
		result[i] = s1[i];

	for (size_t i = 0; i <= len2; i++) // Copy the null terminator too
		result[len1 + i] = s2[i];

	return result;
}
/**
 * _strlen - returns the length of a string.
 * @s: string
 * Return: length of the string
 */

size_t _strlen(const char *s)
{
	size_t length = 0;

	while (s[length] != '\0')
		length++;

	return length;
}
