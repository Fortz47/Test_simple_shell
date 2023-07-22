#include "shell.h"

/**
 * free_arr_str - frees a 2D array
 * @arr: 2d array
 * @i: index stop
 * @j: index start
 */
void free_arr_str(char **arr, int i, int j)
{
	int k;

	for (k = j; k < i; k++)
		free(arr[k]);
}
