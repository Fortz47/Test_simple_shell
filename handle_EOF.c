#include "shell.h"

/**
 */
void handle_EOF(ssize_t *read, char *buffer)
{
	if (*read == -1)
	{
		if (feof(stdin))
		{
			free(buffer);
			write(STDIN_FILENO, "\nlogout\n", 8);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		if (buffer[*read - 1] == '\n')
		{
			buffer[*read - 1] = '\0';
			(*read)--;
		}
		if (_strcmp(buffer, "exit"))
		{
			free(buffer);
			write(STDIN_FILENO, "logout\n", 8);
			exit(EXIT_SUCCESS);
		}
	}
}
