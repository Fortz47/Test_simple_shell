#ifndef SHELL_H
#define SHELL_H

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024
#define MAX_ARG 10

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/**
 */
typedef struct parse
{
	char *cmd;
	char *args[];
} parse;

int _strcmp(const char *s1, const char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
parse *parse_line(char *line);
int handle_EOF(ssize_t read, char **buffer);
int handle_path(parse *parsed);
char *mem_alloc(char *str);
void free_arr_str(char **arr, int i, int j);

#endif
