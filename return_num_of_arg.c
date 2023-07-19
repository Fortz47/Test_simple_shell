#include "shell.h"

/**
 */
int return_num_of_arg(char *buffer)
{
	char *buf, *token;
	int argc;

	argc = 0;
	buf = _strdup(buffer);
	if (!buf)
		return (argc);
	if (token = strtok(buf, " "))
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
