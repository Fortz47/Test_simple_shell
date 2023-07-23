#include "shell.h"

/**
 * _then_free - frees memory
 * @count: number of argument to free
 * @ptr: pointer to struct parse
 *
 * Return: return value
 */
void _then_free(int count, parse *ptr, ...)
{
	va_list list;

	va_start(list, ptr);

	while (count)
	{
		free(va_arg(list, char **));
		count--;
	}
	free(ptr);
	va_end(list);
}
