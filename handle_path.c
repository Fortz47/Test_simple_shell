#include "shell.h"

/**
 */
int handle_path(parse *parse, char *const envp[])
{
	char *filepath, *token;
	int index, status;
	parse *argv;
	pid_t pid;

	char *path = getenv("PATH");

	argv = malloc((sizeof(parse) + sizeof(char *) * (MAX_ARG + 1)););
	if (!argv)
		return (-1);

	argv->cmd = _strdup(parsed->cmd);
	if (!argv->cmd)
	{
		free(argv);
		return (-1);
	}
	for (index = 0; parsed->args[index] != NULL; index++)
	{
		argv->args[index] = _strdup(parsed->args[index]);
		if (argv->args[index] == NULL)
			free_arr_str(argv, index, 0);
		free(argv->cmd);
		free(argv);
		return (-1);
	}

	status = 1;
	argv[index] = NULL;
	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		free_arr_str(argv, index, 0);
		return (-1);
	}
	while (token != NULL)
	{
		strcpy(filepath, token);
		_strcat(filepath, "/");
		_strcat(filepath, parsed->cmd);
		argv->args[0] = _strdup(filepath);
		//printf("filepath: %s\nargv[0]: %s\n", filepath, argv[0]);
		if (check_valid(filepath))
		{
			status = exec_cmd(argv->cmd, argv->args, envp);
			if (status == -1)
			{
				free_arr_str(argv->, index, 0);
				free(filepath);
				return (status);
			}
		}
		free(argv[0]);
		free(filepath);
		token = strtok(NULL, ":");
		if (token)
			filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	}
	free_arr_str(argv, index, 1);
	return (status);
}
