#include "shell.h"

/**
 */
int handle_path(parse *parsed, char **envp)
{
	char *filepath, *token, *path;
	int index, status, flag;
	parse *argv;

	status = 1;
	path = _strdup(getenv("PATH"));
	if (!path)
		return (status);
	argv = malloc(sizeof(parse));
	if (!argv)
	{
		free(path);
		return (status);
	}
	argv->args = malloc(sizeof(char *) * parsed->argc);
	if (!argv->args)
	{
		free(path);
		free(argv);
		return (status);
	}
	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		free(path);
		free(argv->args);
		free(argv);
		return (status);
	}
	flag = FALSE;
	while (token != NULL)
	{
		strcpy(filepath, token);
		_strcat(filepath, "/");
		_strcat(filepath, parsed->cmd);
		argv->cmd = filepath;
		argv->args[0] = filepath;
		if (check_valid(filepath))
		{
			flag = TRUE;
			for (index = 1; index <= parsed->argc; index++)
				argv->args[index] = parsed->args[index];
			status = exec_cmd(argv, envp);
			if (status != 0)
			{
				free(path);
				free(filepath);
				free(argv->args);
				free(argv);
				return (status);
			}
			break;
		}
		free(filepath);
		token = strtok(NULL, ":");
		if (token)
			filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	}
	if (flag && status == 0)
		free(filepath);
	free(path);
	free(argv->args);
	free(argv);
	return (status);
}

/*int main(void)
{
    int i = 0;
    parse *p;
    //char *cmd = strdup("ls -l -a");
    char *buffer = NULL;
    ssize_t len = 0;
    getline(&buffer, &len, stdin);

    char **envp = {NULL};
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
    handle_path(p, envp);

    // Cleanup and free memory
    free(buffer);
    free(p->cmd);
    for (i = 0; p->args[i] != NULL; i++)
        free(p->args[i]);
    free(p->args);
    free(p);

    return 0;
}*/
