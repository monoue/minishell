#include "minishell.h"

void	echo(t_chunk *chunk)
{
	int i;

	i = 1;
	if (!ft_strcmp(chunk->argv[i], "-n"))
	{
		i++;
		while (chunk->argv[i] != 0)
		{
			ft_putstr_fd(chunk->argv[i++], 1);
			if (chunk->argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (chunk->argv[i] != 0)
		{
			ft_putstr_fd(chunk->argv[i++], 1);
			if (chunk->argv[i] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
