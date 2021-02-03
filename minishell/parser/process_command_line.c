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
	char	*line;

	ft_putstr(PROMPT);
	if (get_next_line(STDIN_FILENO, &line) == ERROR)
		exit_err_msg(MALLOC_ERR);
	if (is_quoted_wrongly(line)) // 未完成
	{
		SAFE_FREE(line);
		exit(EXIT_FAILURE);
	}
	// 環境変数をここで整える
	// コメントもここで削る
	exec_one_line(line);
}
