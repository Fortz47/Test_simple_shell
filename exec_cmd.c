#include "shell.h"

/**
 */
int exec_cmd(parse *parsed, char *const envp[])
{
	pid_t pid;
	int wstatus, status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if ((status = execve(parsed->cmd, parsed->args, envp) == -1))
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
