#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	pid_t pid;
	int i;
	ssize_t read;
	char *buffer;
	size_t len;

	while (TRUE)
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
			exit(EXIT_SUCCESS);

		parsed = parse_line(buffer);
		if (!parsed)
			continue;
		pid = fork();
		if (pid == -1)
		{
			dprintf(2,"can't fork process: %s", strerror(errno));
			continue;
		}
		if (pid == 0)
		{
			if ((execv(parsed->cmd, parsed->args)) == -1)
			{
				dprintf(2,"error: %s", strerror(errno));
				continue;
			}
		}
		free(buffer);
		free(parsed->cmd);
		for (i = 0; parsed->args[i] != NULL; i++)
			free(parsed->args[i]);
		free(parsed);
	}
	return (0);
}
