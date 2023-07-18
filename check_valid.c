#include "shell.h"

/**
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
