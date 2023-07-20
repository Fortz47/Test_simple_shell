#include "shell.h"

/**
 */
parse *parse_line(char *line)
{
	extern char *shell;
	parse *ptr;
	char *token;
	int i, ac;

	ac = return_num_of_arg(line);
	token = strtok(line, " ");
	if (!token || !line)
	{
		if (!token)
			perror(shell);
		return (NULL);
	}
	ptr = malloc(sizeof(parse));
	if (ptr == NULL)
	{
		perror(shell);
		return (NULL);
	}
	ptr->argc = ac;
	ptr->cmd = _strdup(token);
	if (!ptr->cmd)
	{
		perror(shell);
		free(ptr);
		return (NULL);
	}
	i = 0;
	ptr->args = malloc(sizeof(char *) * (ac + 1));
	if (!ptr->args)
	{
		free(ptr->cmd);
		free(ptr);
		return (NULL);
	}
	ptr->args[i] = _strdup(token);
	if (!ptr->args[i])
	{
		perror(shell);
		free(ptr->cmd);
		free(ptr);
		return (NULL);
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
				perror(shell);
				free_arr_str(ptr->args, i, 0);
				free(ptr->cmd);
				free(ptr);
				return (NULL);
			}
			i++;
		}
	}
	ptr->args[i] = NULL;
	return (ptr);
}

