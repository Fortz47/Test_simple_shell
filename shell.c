#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	pid_t pid;
	int i, status;
	ssize_t read;
	char *buffer;
	size_t len;

	status = TRUE;
	while (status)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		if (read != -1)
		{
			if (buffer[read - 1] == '\n')
			{
				buffer[read - 1] = '\0';
				read--;
			}
		}
		if (_strcmp((const char *)buffer, "exit"))
		{
			status = FALSE;
			continue;
		}
		parsed = parse_line(buffer);
		if (!parsed)
			continue;
		pid = fork();
		if (pid == -1)
		{
			dprintf(2,"can't fork process: %s\n", strerror(errno));
			continue;
		}
		if (pid == 0)
		{
			if ((execv(parsed->cmd, parsed->args)) == -1)
			{
				dprintf(2,"error: %s\n", strerror(errno));
				kill(pid, SIGTERM);
			}
		}
		free(buffer);
		free(parsed->cmd);
		for (i = 0; parsed->args[i] != NULL; i++)
			free(parsed->args[i]);
		free(parsed);
	}
	free(buffer);
	return (0);
}
