#include "../minishell.h"

bool	is_redirection_char(char c)
{
	return (ft_strchr("><", c));
}

bool	is_pipe_or_break_char(char c)
{
	return (c == '|' || c == ';');
}

bool	is_metachar(char c)
{
	return (is_redirection_char(c) || is_pipe_or_break_char(c));
}

bool	is_space_or_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int		is_quote(char c)
{	
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}