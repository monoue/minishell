#include "minishell.h"

void	process_command_line(char *line, t_list *envp)
{
	char	**commands;
	size_t	index;
	// char	*tmp;

	// ここで、空のヤツを置き換え
	// tmp = remove_undefined_env(line, envp);
	// commands = ft_split_skipping_quotes(tmp, ';');
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
