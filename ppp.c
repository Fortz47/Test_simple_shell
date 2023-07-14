#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
	char *buffer = NULL;
	size_t len = 0;

	getline(&buffer, &len, stdin);
	int i = 0;
	char buf[1024];
	while (buffer[i] != '\n')
	{
		buf[i] = buffer[i];
		i++;
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		dprintf(2, "can't fork process: %s", strerror(errno));
		exit(1);
	}
	if (pid == 0)
	{
		if (execl(buf, buf, NULL) == -1)
		{
			dprintf(2, "failed to execute: %s", strerror(errno));
			exit(1);
		}
	}
	return 0;
}
