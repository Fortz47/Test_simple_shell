#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	int i;
	ssize_t read;
	char *buffer, *shell;
	size_t len;

	char *const envp[] = {NULL};

	shell = av[0];
	while (TRUE)
	{
		buffer = NULL;
		len = 0;
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&buffer, &len, stdin);
		if ((read = handle_EOF(read, &buffer)) == -1)
		{
			printf("cant getline");
			perror(shell);
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
