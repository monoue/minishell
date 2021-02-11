#include "minishell.h"

static t_element_type	get_element_type(char *element)
{
	if (!element)
		return (NEWLINE);
	if (is_redirection_str(element))
		return (REDIRECTION);
	if (is_pipe_or_break_str(element))
		return (PIPE_OR_BREAK);
	return (WORD);
}

static bool				is_valid_order(t_element_type types[2])
{
	const t_element_type	invalid_combs[6][2] = {
		{START, PIPE_OR_BREAK},
		{PIPE_OR_BREAK, PIPE_OR_BREAK},
		{REDIRECTION, PIPE_OR_BREAK},
		{REDIRECTION, REDIRECTION},
		{REDIRECTION, NEWLINE},
		{ELEMENT_TYPES_NUM, ELEMENT_TYPES_NUM}
	};
	size_t					index;

	index = 0;
	while (invalid_combs[index][0] != ELEMENT_TYPES_NUM)
	{
		if (types[0] == invalid_combs[index][0]
			&& types[1] == invalid_combs[index][1])
		{
			return (false);
		}
		index++;
	}
	return (true);
}

static void				swap(t_element_type *p1, t_element_type *p2)
{
	t_element_type	tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static int				get_problematic_element(char **command_line_words)
{
	size_t			index;
	size_t			words_num;
	t_element_type	types[2];

	words_num = ft_count_strs((const char**)command_line_words);
	if (words_num == 0)
		return (SYNTAX_VALID);
	types[0] = START;
	index = 0;
	while (index <= words_num)
	{
		types[1] = get_element_type(command_line_words[index]);
		if (!is_valid_order(types))
			return (index);
		swap(&types[0], &types[1]);
		index++;
	}
	return (SYNTAX_VALID);
}

int						check_syntax(char *command_line, char **command_line_words)
{
	if (is_quoted_wrongly(command_line))
		return (SYNTAX_QUOTED_WRONGLY);
	return (get_problematic_element(command_line_words));
}

bool	put_message_if_syntax_error(char *command_line)
{
	char	**words;
	int		ret;

	words = split_command_line(command_line);
	ret = check_syntax(command_line, words);
	if (ret == SYNTAX_QUOTED_WRONGLY || ret == SYNTAX_VALID)
		ft_free_split(words);
	if (ret == SYNTAX_QUOTED_WRONGLY)
	{
		ft_putstr_err("-bash: quotes not closed\n");
		return (true);
	}
	if (ret != SYNTAX_VALID)
	{
		ft_putstr_err("-bash: syntax error near unexpected token `");
		if (words[ret])
			ft_putstr_err(words[ret]);
		else
			ft_putstr_err("newline");
		ft_free_split(words);
		ft_putstr_err("`\n");
		return (true);
	}
	return (false);
}
