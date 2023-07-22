#include "shell.h"

/**
 * handle_path - appends command input to PATH
 * @parsed: pointer to struct parse
 * @envp: array of environment variables
 *
 * Return: 0 if command exist on PATH or 1 if not
 */
int handle_path(parse *parsed, char **envp)
{
	char *filepath, *token, *path;
	int index, flag;
	parse *argv;
	char status;

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
		then_free(1, &status, argv, &path);
		/*free(path);
		free(argv);
		return (status);*/
	}
	token = strtok(path, ":");
	filepath = malloc(strlen(token) + strlen(parsed->cmd) + 2);
	if (!filepath)
	{
		then_free(2, &status, argv, &path, argv->args);
		/*free(path);
		free(argv->args);
		free(argv);
		return (status);*/
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
				then_free(3, &status, argv, &path, &filepath, argv->args);
				/*free(path);
				free(filepath);
				free(argv->args);
				free(argv);
				return (status);*/
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
	then_free(2, &status, argv, &path, argv->args);
	/*free(path);
	free(argv->args);
	free(argv);*/
	return (status);
}
