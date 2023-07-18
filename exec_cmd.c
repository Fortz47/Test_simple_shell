#include "shell.h"

/**
 */
int exec_cmd(parse *parsed, char *const envp[])
{
	pid_t pid;

	int status = 1;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if ((status = execve(parsed->cmd, parsed->args, envp)) == -1)
			exit(EXIT_FAILURE);
	}
	return (status);
}
