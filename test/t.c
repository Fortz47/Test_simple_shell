#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	char *s = "error";
	if (execl("/bin/l", "/bin/l", "-l", "-a", NULL) == -1)
		perror(s);
	return (0);
}
