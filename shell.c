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

	shell = av[0];
	status = TRUE;
	while (status)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		if ((read = handle_EOF(read, &buffer)) == -1)
		{
			perror(shell);
			continue;
		}
		parsed = parse_line(buffer);
		if (!parsed)
			continue;
		if (handle_path(parsed) == -1)
		{
			perror(shell);
		}
		free(buffer);
		free(parsed->cmd);
		for (i = 0; parsed->args[i] != NULL; i++)
			free(parsed->args[i]);
		free(parsed);
	}
	return (0);
}
