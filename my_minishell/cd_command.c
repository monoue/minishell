#include "minishell.h"

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir("/") == ERROR)
			perror("");
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			perror("");
	}
	return 1;
}
