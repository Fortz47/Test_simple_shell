#include "shell.h"

/**
 */
char *mem_alloc(char *str)
{
	char *ptr;
	int i;

	ptr = malloc(sizeof(char) * BUFFER_SIZE);
	if (!ptr)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		ptr[i] = str[i];
	ptr[i] = '/';
	ptr[i + 1] = '\0';
	return (ptr);
}
