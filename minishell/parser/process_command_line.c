#include "../minishell.h"

static void	exec_one_line(char *line, t_list *envp)
{
	char	**commands;	
	size_t	index;
	
	commands = ft_split_considering_quotes(line, ';');
	index = 0;
	while (commands[index])	
	{
		process_one_command(commands[index], envp);
		index++;
	}
	ft_free_split(commands);
}

void		process_command_line(char *line, t_list *envp)
{
	exec_one_line(line, envp);
}
