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
