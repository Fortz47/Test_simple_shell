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

	while (token)
	{
		filepath = _strcat(token, cmd);
		access = access(filepath, X_OK);
		st = stat(filepath, &sb);
		if (!access && !st && S_ISREG(sb.st_mode))
		{
			
		}
	}
}
