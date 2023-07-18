#include "shell.h"

/**
 */
void free_arr_str(char **arr, int i, int j)
{
	int k;

	for (k = j; k < i; k++)
		free(arr[k]);
}
