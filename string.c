#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if equal, else a -ve or +ve int
 */

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	if (s1 == NULL && s2 == NULL)
		return (1);
	else if (s1 == NULL)
		return (0);
	else if (s2 == NULL)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}

	return (1);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter.
 * @str: string parameter
 *
 * Return: pointer to new string or Null
 *
 */

char *_strdup(char *str)
{
	char *arr;
	int i, len;

	if (str == NULL)
		return (NULL);
	len = 0;
	while (str[len])
		len++;

	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
