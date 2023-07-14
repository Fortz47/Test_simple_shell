#include "shell.h"

/**
 */
parse *parse_line(char *line)
{
	parse *ptr;
	char *token;
	int i;

	const char *dilim = " -";

	ptr = malloc(sizeof(parse *));
	if (!ptr)
		return (NULL);
	token = strtok(line, dilim);
	ptr->cmd = _strdup(token);
	ptr->args[0] = _strdup(token);
	i = 1;
	while (token != NULL)
	{
		token = strtok(NULL, dilim);
		ptr->args[i] = _strdup(token);
		i++;
	}
	ptr->args[i] = NULL;
	return (ptr);
}
