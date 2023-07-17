#include "shell.h"

/**
 */
int handle_path(char *cmd)
{
	struct stat sb;
	char *filepath;
	int access, st;

	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char *const argv[] = {cmd, NULL};
	char *const arvp[] = {NULL};
	int status = FALSE;

	while (token)
	{
		filepath = _strcat(token, cmd);
		access = access(filepath, X_OK);
		st = stat(filepath, &sb);
		if (!access && !st && S_ISREG(sb.st_mode))
		{
			pid = fork();
			if (pid == -1)
				return (TRUE);
			if (pid == 0)
			{
				if (execve(filepath, argv, arvp) == -1)
				{
					status = TRUE;
					exit(EXIT_FAILURE);
				}
			}
			break;
		}
		token = strtok(NULL, ":");
	}
	return (status);
}
