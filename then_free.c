#include "shell.h"

/**
 * then_free - frees memory
 * @count: number of argument to free
 * @_return: return value
 * @ptr: pointer to struct parse
 *
 * Return: return value
 */
parse *then_free(int count, parse *_return, parse *ptr, ...)
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
