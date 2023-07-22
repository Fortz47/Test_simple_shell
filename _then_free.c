#include "shell.h"

/**
 * _then_free - frees memory
 * @count: number of argument to free
 * @_return: return value
 * @ptr: pointer to struct parse
 *
 * Return: return value
 */
int _then_free(int count, int _return, parse *ptr, ...)
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
	return (_return);
}
