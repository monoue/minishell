#include "minishell.h"

void	wc(char *fullpath_cmd, t_chunk *chunk, char **environ)
{
	fullpath_cmd = ft_strjoin("/usr/bin/", chunk->argv[0]);
	if (!fullpath_cmd)
		perror("");
	else if (execve(fullpath_cmd, chunk->argv, environ) == ERROR)
	{	
		// ft_putstr("")
	}
	SAFE_FREE(fullpath_cmd);
}
