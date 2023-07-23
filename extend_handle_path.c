#include "shell.h"
/**
 * then - continuation of handle_path function
 * @fp: filepath
 * @t: token
 * @p: pointer to struct parse
 * @av: pointer to struct parse
 * @flag: flag
 * @pt: path
 * @s: status
 */
void then(char *fp, char *t, parse *p, parse *av, int *flag, char *pt, int *s)
{
	int index;
	char **envp = environ;

	while (t != NULL)
	{
		_strcpy(fp, t);
		_strcat(fp, "/");
		_strcat(fp, p->cmd);
		av->cmd = _strdup(fp);
		av->args[0] = _strdup(fp);
		if (check_valid(fp))
		{
			*flag = TRUE;
			for (index = 1; index < p->argc; index++)
				av->args[index] = _strdup(p->args[index]);
			av->args[index] = NULL;
			*s = exec_cmd(av, envp);
			if (*s != 0)
			{
				_then_free(4, av, &pt, &fp, &av->cmd, av->args);
				return;
			}
			break;
		}
		free(fp);
		free(av->cmd);
		free(av->args[0]);
		t = strtok(NULL, ":");
		if (t != NULL)
			fp = malloc(sizeof(char) * (_strlen(t) + _strlen(p->cmd) + 2));
	}
	if (flag && *s == 0)
	{
		free(fp);
		free(av->cmd);
		free_arr_str(av->args, index, 0);
	}
	free(pt);
	free(av->args);
	free(av);
}
