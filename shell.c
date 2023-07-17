#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	pid_t pid;
	int i, status;
	ssize_t read;
	char *buffer, *shell;
	size_t len;

	char *const envp[] = {"PATH=/usr/local/bin:/usr/bin:$PATH", NULL};

	shell = av[0];
	status = TRUE;
	/*if (load_config() == -1)
	{
		perror(shell);
		exit(EXIT_FAILURE);
	}*/
	while (status)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		if ((read = handle_EOF(read, &buffer)) == -1)
		{
			dprintf(STDERR_FILENO, "%s: %s\n", shell, strerror(errno));
			continue;
		}
		parsed = parse_line(buffer);
		if (!parsed)
			continue;
		pid = fork();
		if (pid == -1)
		{
			dprintf(STDERR_FILENO, "%s: %s\n", shell, strerror(errno));
			continue;
		}
		if (pid == 0)
		{
			if ((execve(parsed->cmd, parsed->args, envp)) == -1)
			{
				dprintf(STDERR_FILENO, "%s: %s\n", shell, strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		free(buffer);
		free(parsed->cmd);
		for (i = 0; parsed->args[i] != NULL; i++)
			free(parsed->args[i]);
		free(parsed);
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
	free(buffer);
	return (0);
}
