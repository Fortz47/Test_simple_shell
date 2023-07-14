#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 10

typedef struct parse
{
    char *cmd;
    char *args[];
} parse;

parse *parse_line(char *line)
{
    parse *ptr;
    char *token;
    int i = 0;

    ptr = malloc(sizeof(parse) + sizeof(char*) * (MAX_ARGS + 1));
    if (!ptr)
        return NULL;

    const char *dilim = " ";
    token = strtok(line, dilim);
    ptr->cmd = strdup(token);
    ptr->args[i] = strdup(token);
    i++;

    while (token != NULL && i < MAX_ARGS)
    {
        token = strtok(NULL, dilim);
        ptr->args[i] = strdup(token);
        i++;
    }
    ptr->args[i] = NULL;

    return ptr;
}

int main()
{
    parse *parsed;
    char *buffer = "hello -l -a me";

    parsed = parse_line(buffer);
    for (int i = 0; parsed->args[i] != NULL; i++)
    {
        printf("arg[%d]: %s\n", i, parsed->args[i]);
    }

    free(parsed->cmd);
    for (int i = 0; parsed->args[i] != NULL; i++)
    {
        free(parsed->args[i]);
    }
    free(parsed);

    puts("Done");
    return 0;
}

