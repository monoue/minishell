#include "../minishell.h"

typedef enum	{
	FIRST,
	PIPE_OR_BREAK,
	REDIRECTION,
	NEWLINE,
	WORD,

	FLAG_TYPES_NUM
}		element_type;

element_type	get_element_type(char *element)
{
	if (!element)
		return (NEWLINE);
	if (is_redirection_str(element))
		return (REDIRECTION);
	if (is_pipe_or_break_str(element))
		return (PIPE_OR_BREAK);
	return (WORD);
}

#define SYNTAX_VALID			-1
#define SYNTAX_QUOTED_WRONGLY	-2

static bool	is_valid_order(element_type types[2])
{
	const element_type	invalid_combs[6][2] = {
		{FIRST, PIPE_OR_BREAK},
		{PIPE_OR_BREAK, PIPE_OR_BREAK},
		{REDIRECTION, PIPE_OR_BREAK},
		{REDIRECTION, REDIRECTION},
		{REDIRECTION, NEWLINE},
		{FLAG_TYPES_NUM, FLAG_TYPES_NUM}
	};
	size_t				index;

	index = 0;
	while (invalid_combs[index][0] != FLAG_TYPES_NUM)
	{
		if (types[0] == invalid_combs[index][0] && types[1] == invalid_combs[index][1])
			return (false);
		index++;
	}
	return (true);
}

static int	get_order_type(char *command_line)
{
	char	**words;
	size_t	index;
	size_t	words_num;
	element_type	types[2];
	element_type	tmp;

	words = split_command_line(command_line);
	words_num = ft_count_strs((const char**)words);
	if (words_num == 0)
		return (SYNTAX_VALID);
	types[0] = FIRST;
	index = 0;
	while (index <= words_num)
	{
		types[1] = get_element_type(words[index]);
		if (!is_valid_order(types))
			return (index);
		tmp = types[0];
		types[0] = types[1];
		types[1] = tmp;
		index++;
	}
	return (SYNTAX_VALID);
}

int		get_syntax_type(char *command_line)
{
	if (is_quoted_wrongly(command_line))
		return (SYNTAX_QUOTED_WRONGLY); // bool 型ではなく、エラーメッセージを返すべき
	return (get_order_type(command_line));
}

