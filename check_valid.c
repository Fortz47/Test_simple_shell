#include "shell.h"

/**
 * check_valid - check if a file exists, is executable
 * and is a regular file.
 * @filepath: file to check
 *
 * Return: True(1), or False(0)
 */
int check_valid(char *filepath)
{
	struct stat sb;
	int Access, st;

	Access = access(filepath, X_OK);
	st = stat(filepath, &sb);

	if (!Access && !st && S_ISREG(sb.st_mode))
		return (TRUE);
	return (FALSE);
}
