#include "shell.h"

/**
 */
int handle_path(parse *parsed, char *const envp[])
{
	char *filepath, *token;
	int index, status;
	parse *argv;

	puts("----starting----\n");
	char *path = getenv("PATH");
	int flag = FALSE;

	argv = malloc(sizeof(parse) + sizeof(char *) * (MAX_ARG + 1));
	if (!argv)
		return (-1);
	
	status = 1;
	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		free(argv);
		return (-1);
	}
	while (token != NULL)
	{
		strcpy(filepath, token);
		_strcat(filepath, "/");
		_strcat(filepath, parsed->cmd);
		argv->cmd = filepath;
		argv->args[0] = filepath;
		printf("filepath: %s\nargv[0]: %s\n", filepath, argv->args[0]);
		if (check_valid(filepath))
		{
			flag = TRUE;
			for (index = 1; parsed->args[index] != NULL; index++)
				argv->args[index] = parsed->args[index];
			argv->args[index] = NULL;
			status = exec_cmd(argv, envp);
			printf("----status: %d----\n", status);
			if (status != 0)
			{
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
	free(argv);
	return (status);
}

/*int main(void)
{
	parse *p = malloc(sizeof(parse) + sizeof(char *) * 3);
	p->cmd = _strdup("ls");
	p->args[0] = _strdup("ls");
	p->args[1] = _strdup("-l");
	p->args[2] = NULL;


	char *const envp[] = {NULL};

	int status = handle_path(p, envp);

	printf("status: %d\n", status);
	for (int i = 0; p->args[i] != NULL; i++)
		free(p->args[i]);
	free(p->cmd);
	free(p);

	return 0;
}*/
