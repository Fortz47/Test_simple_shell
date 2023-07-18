#include "shell.h"

/**
 */
int handle_EOF(ssize_t read, char **buffer)
{
	char *buf;

	buf = *buffer;
	if (read == -1)
	{
		if (feof(stdin))
		{
			write(STDIN_FILENO, "\nlogout\n", 8);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		if (buf[read - 1] == '\n')
		{
			(buf[read - 1] = '\0');
			read--;
		}
		if (_strcmp(buf, "exit"))
		{
			free(buffer);
			write(STDIN_FILENO, "logout\n", 8);
			exit(EXIT_SUCCESS);
		}
	}
	return (read);
}
