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
		printf("cmd: %s\n", parsed->cmd);
		for (int i = 0; parsed->args[i]; i++)
		{
			printf("arg[%d]: %s\n", i, parsed->args[i]);
		}
		if (parsed)
		{
			int ln = handle_path(parsed, envp);
			printf("handle path: %d\n", ln);
			if (ln == 1)
			{
				//if (exec_cmd(parsed, envp) == -1)
				int err = exec_cmd(parsed, envp);
				printf("No_path: %d\n", err);
				if (err != 0)
					perror(shell);
			}
			free(parsed->cmd);
			for (i = 0; parsed->args[i] != NULL; i++)
				free(parsed->args[i]);
			free(parsed);
		}
		free(buffer);
	}
	return (0);
}
