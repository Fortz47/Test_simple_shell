#include "shell.h"

/**
 */
int main(int ac, char *av[])
{
	parse *parsed;
	pid_t pid;

	char *buffer = NULL;
	size_t len = 0;

	while (TRUE)
	{
		write(STDOUT_FILENO, "($) ", 4);
		getline(&buffer, &len, stdin);
		if (_strcmp((const char *)buffer, "exit\n"))
			return (0);
		parsed = parse_line(buffer);
		for (int i = 0; parsed->args[i] != NULL; i++)
		{
			printf("arg[%d]: %s\n", i, parsed->args[i]);
		}
		/*pid = fork();
		if (pid == -1)
		{
			dprintf(2,"error: %s", strerror(errno));
			continue;
		}
		if (pid == 0)
		{
			if ((execv(parsed->cmd, parsed->args)) == -1)
			{
				dprintf(2,"error: %s", strerror(errno));
				continue;
			}
		}*/
	}
	return (0);
}
