#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	int i;
	ssize_t read;
	char *buffer;
	size_t len;

	char *const envp[] = {NULL};

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

		parsed = parse_line(buffer, read);
		if (parsed)
		{
			if (handle_path(parsed, envp) != 0)
			{
				if (exec_cmd(parsed, envp) != 0)
					perror(av[0]);
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
