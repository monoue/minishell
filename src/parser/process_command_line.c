#include "minishell.h"

void	process_command_line(char *line, t_list *envp)
{
	char	**commands;
	size_t	index;

	commands = ft_split_skipping_quotes(line, ';');
	if (!commands)
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (commands[index])
	{
		process_one_command(commands[index], envp);
		index++;
	}
	ft_free_split(commands);
}
