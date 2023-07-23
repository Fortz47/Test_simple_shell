#include "shell.h"

/**
 * _atoi - converts a string to int
 * @str: string
 *
 * Return: converted string
 */
int _atoi(char *str)
{
	int i = 0, sign = 1;
	int num = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + (str[i] - '0');
		else
			break;
		i++;
	}
	return (num * sign);
}

/**
 * exec_cmd - executes a shell command
 * @parsed: pointer to struct parse
 * @envp: array of strings containing environment variables
 *
 * Return: 0 if successful, 1 is not
 */
int exec_cmd(parse *parsed, char **envp)
{
	pid_t pid;
	int wstatus, status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		status = execve(parsed->cmd, parsed->args, envp);
		if (status == -1)
			exit(status);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			status = WEXITSTATUS(wstatus);
	}
	return (status);
}

/**
 * free_arr_str - frees a 2D array
 * @arr: 2d array
 * @i: index stop
 * @j: index start
 */
void free_arr_str(char **arr, int i, int j)
{
	int k;

	for (k = j; k < i; k++)
		free(arr[k]);
}

/**
 * return_num_of_arg - returns no. of args(strings) in
 * an array
 * @buffer: array
 *
 * Return: no of args(strings)
 */
int return_num_of_arg(char *buffer)
{
	char *buf, *token;
	int argc;

	argc = 0;
	buf = _strdup(buffer);
	if (!buf)
		return (argc);
	token = strtok(buf, " ");
	if (token)
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

/**
 * check_valid - check if a file exists, is executable
 * and is a regular file.
 * @filepath: file to check
 *
 * Return: True(1), or False(0)
 */
int check_valid(char *filepath)
{
	struct stat sb;
	int Access, st;

	Access = access(filepath, X_OK);
	st = stat(filepath, &sb);

	if (!Access && !st && S_ISREG(sb.st_mode))
		return (TRUE);
	return (FALSE);
}
