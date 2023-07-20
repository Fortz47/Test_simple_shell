#include "shell.h"

/**
 */
int main(int ac __attribute__((unused)), char *av[])
{
	parse *parsed;
	int i;
	ssize_t read;
	char *buffer;
	size_t len;

	char **envp = environ;
	char *shell = av[0];

	while (TRUE)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		handle_EOF(&read, &buffer);
		if (!read)
		{
			free(buffer);
			continue;
		}

		parsed = parse_line(buffer);
		if (parsed)
		{
			if (handle_path(parsed, envp) != 0)
			{
				if (exec_cmd(parsed, envp) != 0)
					perror(shell);
			}
			free(buffer);
			free(parsed->cmd);
			for (i = 0; parsed->args[i] != NULL; i++)
				free(parsed->args[i]);
			free(parsed);
		}
	}
	return (0);
}
