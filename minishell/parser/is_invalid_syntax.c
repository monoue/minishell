#include "minishell.h"

static bool	is_invalid_order(char *command_line)
{
	char	**words;
	size_t	index;
	size_t	words_num;
	char	last_c;
	int		flag;
	// enum 作る
	// FIRST
	// PIPE_OR_BREAK
	// REDIRECTION

	flag = 


	words = split_command_line(command_line);
	words_num = ft_count_strs(words);
	if (words_num == 0)
		return (false);
	if (is_pipe_or_break(words[0][0]))	
		return (true);
	// これは判断するのが後ろみたい
	last_c = words[words_num - 1][ft_strlen(words[words_num - 1]) - 1];
	if (is_redirection_char(last_c))
		return (true);
	
}

bool		is_invalid_syntax(char *command_line)
{
	return (is_quoted_wrongly(command_line) || is_invalid_order(command_line));
}
