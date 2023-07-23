/*#include "shell.h"*/
#include <stdio.h>

/**
 * _atoi - converts a string to int
 * @str: string
 *
 * Return: converted string
 */
int _atoi(char *str)
{
	int i = 0, sign = 1;
	int num = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else
			break;
		i++;
	}
	return (num * sign);
}
