#include "shell.h"

/**
 */
parse *parse_line(char *line)
{
	parse *ptr;
	char *token;
	int argc, i;

	const char *delim = " ";

	token = strtok(line, delim);
	if (!token || !line)
		return (NULL);
	ptr = malloc(sizeof(parse) + sizeof(char *) * (MAX_ARG + 1));
	if (ptr == NULL)
		return (NULL);
	ptr->cmd = _strdup(token);
	if (!ptr->cmd)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		free(ptr);
		return (NULL);
	}
	i = 0;
	ptr->args[i] = _strdup(token);
	if (!ptr->args[i])
	{
		fprintf(stderr, "Memory allocation failed.\n");
		free(ptr->cmd);
		free(ptr);
		return NULL;
	}
	i++;
	while (token != NULL && i < MAX_ARG)
	{
		token = strtok(NULL, delim);
		if (token)
		{
			ptr->args[i] = _strdup(token);
			if (!ptr->args[i])
			{
				fprintf(stderr, "Memory allocation failed.\n");
				for (int j = 0; j < i; j++)
					free(ptr->args[j]);
				free(ptr->cmd);
				free(ptr);
				return NULL;
			}
			i++;
		}
	}
	ptr->args[i] = NULL;
	return (ptr);
}

