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
	argv = malloc(sizeof(parse) + sizeof(char *) * (parsed->argc + 1));
	if (!argv)
	{
		free(path);
		return (status);
	}

	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		free(path);
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
			for (index = 1; parsed->args[index] != NULL; index++)
				argv->args[index] = parsed->args[index];
			argv->args[index] = NULL;
			status = exec_cmd(argv, envp);
			if (status != 0)
			{
				free(path);
				free(filepath);
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
	free(argv);
	return (status);
}
