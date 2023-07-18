#include "shell.h"

/**
 */
int handle_path(parse *parsed)
{
	struct stat sb;
	char *filepath, *token; //*append_path;
	int Access, st, i, j, status;
	char *argv[MAX_ARG];
	pid_t pid;

	char *path = getenv("PATH");
	char *const envp[] = {NULL};

	for (i = 0; parsed->args[i] != NULL; i++)
	{
		argv[i] = _strdup(parsed->args[i]);
		if (argv[i] == NULL)
			free_arr_str(argv, i, 0);
	}
	argv[i] = NULL;
	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		free_arr_str(argv, i, 0);
		return (-1);
	}
	while (token != NULL)
	{
		strcpy(filepath, token);
		_strcat(filepath, "/");
		_strcat(filepath, parsed->cmd);
		argv[0] = _strdup(filepath);
		printf("filepath: %s\nargv[0]: %s\n", filepath, argv[0]);
		Access = access(filepath, X_OK);
		st = stat(filepath, &sb);
		if (!Access && !st && S_ISREG(sb.st_mode))
		{
			pid = fork();
			if (pid == -1)
			{
				i = 0;
				while (argv[i])
				{
					free(argv[i]);
					i++;
				}
				return (-1);
			}
			if (pid == 0)
			{
				if ((status = execve(filepath, argv, envp) == -1))
					exit(EXIT_FAILURE);
			}
			free(argv[0]);
			free(filepath);
			break;
		}
		free(argv[0]);
		free(filepath);
		token = strtok(NULL, ":");
		if (token)
			filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	}
	free_arr_str(argv, i, 1);
	if (status == -1)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if ((status = execve(parsed->cmd, parsed->args, envp)) == -1)
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}
