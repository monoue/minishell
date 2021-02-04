#include "../minishell.h"

static void	exec_one_line(char *line)
{
	char	**commands;	
	size_t	index;
	
	commands = ft_split_considering_quotes(line, ';');
	index = 0;
	while (commands[index])	
	{
		process_one_command(commands[index]);
		index++;
	}
	ft_free_split(commands);
}

void		process_command_line(void)
{
	char	*command_line;

	ft_putstr(PROMPT);
	if (get_next_line(STDIN_FILENO, &command_line) == ERROR)
		exit_err_msg(MALLOC_ERR);
	// if (check_syntax(command_line)) // 未完成
	// {
	// 	SAFE_FREE(command_line);
	// 	exit(EXIT_FAILURE);
	// }
	// 環境変数をここで整える
	// コメントもここで削る
	exec_one_line(command_line);
}
