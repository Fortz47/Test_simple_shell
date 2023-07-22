#include "shell.h"

/**
 * return_num_of_arg - returns no. of args(strings) in
 * an array
 * @buffer: array
 *
 * Return: no of args(strings)
 */
int return_num_of_arg(char *buffer)
{
	char *buf, *token;
	int argc;

	argc = 0;
	buf = _strdup(buffer);
	if (!buf)
		return (argc);
	token = strtok(buf, " ");
	if (token)
		argc++;
	while (token)
	{
		token = strtok(NULL, " ");
		if (token)
			argc++;
	}
	free(buf);
	return (argc);
}
