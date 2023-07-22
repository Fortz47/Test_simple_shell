#include "shell.h"

/**
 * parse_line - parses a string
 * @line: string
 * Return: pointer to a struct parse
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
	ptr = malloc(sizeof(parse));
	if (ptr == NULL)
		return (NULL);
	ptr->argc = ac;
	ptr->cmd = _strdup(token);
	if (!ptr->cmd)
		then_free(0, NULL, ptr);
	ptr->args = malloc(sizeof(char *) * (ac + 1));
	if (!ptr->args)
		then_free(1, NULL, ptr, &ptr->cmd);
	ptr->args[0] = _strdup(token);
	if (!ptr->args[0])
		then_free(2, NULL, ptr, &ptr->cmd, ptr->args);
	for (i = 1; i < ac; i++)
	{
		token = strtok(NULL, " ");
		ptr->args[i] = _strdup(token);
		if (!ptr->args[i])
		{
			free_arr_str(ptr->args, i, 0);
			then_free(2, NULL, ptr, &ptr->cmd, ptr->args);
		}
	}
	ptr->args[i] = NULL;
	return (ptr);
}
