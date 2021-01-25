#include "minishell.h"

void		pwd(t_chunk *chunk)
{
	if (chunk->argv[1])
		{
			ft_putstr("pwd: too many arguments\n");
			exit(EXIT_FAILURE);
		}
		ft_putstr(getcwd(NULL, 0));
		ft_putchar('\n');
}
