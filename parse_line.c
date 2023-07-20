#include "shell.h"

/**
 */
parse *parse_line(char *line)
{
	parse *ptr;
	char *token;
	int i, ac;

	ac = return_num_of_arg(line);
	token = strtok(line, " ");
	if (!token || !line)
		return (NULL);
	ptr = malloc(sizeof(parse) + sizeof(char *) * (ac + 1));
	if (ptr == NULL)
		return (NULL);
	ptr->argc = ac;
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
	while (token != NULL)
	{
		token = strtok(NULL, " ");
		if (token)
		{
			ptr->args[i] = _strdup(token);
			if (!ptr->args[i])
			{
				fprintf(stderr, "Memory allocation failed.\n");
				free_arr_str(ptr->args, i, 0);
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

