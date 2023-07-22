#include "shell.h"

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
