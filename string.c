#include "shell.h"

/**
 * _strlen - returns the lenght of a string
 * @s: parameter
 * Return: lenght of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * _strcpy - copies the string pointed to by src, including the
 * terminating null byte (\0), to the buffer pointed to by dest
 * @dest: function parameter 1
 * @src: function parameter 2
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	if (!src)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 1 if equal, else 0
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


/**
 * _strcat - concatenate two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: appended string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
