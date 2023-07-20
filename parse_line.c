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
	ptr = malloc(sizeof(parse));
	if (ptr == NULL)
		return (NULL);
	ptr->argc = ac;
	ptr->cmd = _strdup(token);
	if (!ptr->cmd)
	{
		free(ptr);
		return (NULL);
	}
	ptr->args = malloc(sizeof(char *) * (ac + 1));
	if (!ptr->args)
	{
		free(ptr->cmd);
		free(ptr);
		return (NULL);
	}
	ptr->args[0] = _strdup(token);
	if (!ptr->args[0])
	{
		free(ptr->cmd);
		free(ptr->args);
		free(ptr);
		return (NULL);
	}
	for (i = 1; i < ac; i++)
	{
		token = strtok(NULL, " ");
		ptr->args[i] = _strdup(token);
		if (!ptr->args[i])
		{
			free_arr_str(ptr->args, i, 0);
			free(ptr->cmd);
			free(ptr->args);
			free(ptr);
			return (NULL);
		}
	}
	ptr->args[i] = NULL;
	return (ptr);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parse
{
	int argc;
	char *cmd;
	char **args;
} parse;

void free_arr_str(char **arr, int i, int j)
{
	int k;

	for (k = j; k < i; k++)
		free(arr[k]);
}

int return_num_of_arg(char *buffer)
{
	char *buf, *token;
	int argc;

	argc = 0;
	buf = strdup(buffer);
	if (!buf)
		return (argc);
	if ((token = strtok(buf, " ")))
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

parse *parse_line(char *line)
{
    parse *ptr;
    char *token;
    int i, ac;

    ac = return_num_of_arg(line);
    printf("Number of arguments: %d\n", ac);
    token = strtok(line, " ");
    if (!token || !line)
        return NULL;

    ptr = malloc(sizeof(parse));
    if (ptr == NULL)
        return NULL;

    ptr->argc = ac;
    ptr->cmd = strdup(token);
    if (!ptr->cmd)
    {
        free(ptr);
        return NULL;
    }

    ptr->args = malloc(sizeof(char *) * (ac + 1));
    if (!ptr->args)
    {
        free(ptr->cmd);
        free(ptr);
        return NULL;
    }

    // Store the command at index 0 of args array
    ptr->args[0] = strdup(token);
    if (!ptr->args[0])
    {
        free(ptr->cmd);
        free(ptr->args);
        free(ptr);
        return NULL;
    }

    for (i = 1; i < ac; i++)
    {
        token = strtok(NULL, " ");
        ptr->args[i] = strdup(token);
        if (!ptr->args[i])
        {
            free_arr_str(ptr->args, i, 0);
            free(ptr->cmd);
            free(ptr->args);
            free(ptr);
            return NULL;
        }
    }

    // Set the last element of args array to NULL to terminate it
    ptr->args[i] = NULL;

    // Debug print statements to check args array
    printf("Command: %s\n", ptr->cmd);
    for (i = 0; i < ac; i++)
    {
        printf("Arg %d: %s\n", i, ptr->args[i]);
    }

    return ptr;
}


int main(void)
{
    int i = 0;
    parse *p;
    //char *cmd = strdup("ls -l -a");
    char *buffer = NULL;
    ssize_t len = 0;
    getline(&buffer, &len, stdin);

    buffer[len - 1] = '\0';
    p = parse_line(buffer);
    if (!p) {
        printf("Failed to parse the command.\n");
        return 1;
    }

    puts(p->cmd);
    while (p->args[i] != NULL)
    {
        puts(p->args[i]);
        i++;
    }

    // Cleanup and free memory
    free(buffer);
    free(p->cmd);
    for (i = 1; p->args[i] != NULL; i++)
        free(p->args[i]);
    free(p->args);
    free(p);

    return 0;
}*/

