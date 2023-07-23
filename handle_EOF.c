#include "shell.h"

/**
 * handle_EOF - checks for EOF(ctrl + D) and/or "exit"
 * @read: number of characters read(from stdin)
 * @buffer: pointer to read input(from stdin)
 */
void handle_EOF(ssize_t *read, char *buffer)
{
	char *token, buf[BUFFER_SIZE];
	int status;

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
		_strcpy(buf, buffer);
		token = strtok(buf, " ");
		if (_strcmp(token, "exit"))
		{
			free(buffer);
			token = strtok(NULL, " ");
			if (token)
			{
				status = _atoi(token);
				write(STDIN_FILENO, "logout\n", 8);
				exit(status);
			}
			exit(EXIT_SUCCESS);
		}
	}
}
