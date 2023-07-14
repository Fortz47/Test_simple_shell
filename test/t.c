#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	if (execl("/bin/ls", "/bin/ls", "-l", "-a", NULL) == -1)
		dprintf(2, "error: %s", strerror(errno));
	return (0);
}
