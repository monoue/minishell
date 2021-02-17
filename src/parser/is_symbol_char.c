/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:42 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:27:44 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_quote_char(char c)
{
	return (c == '\'' || c == '\"');
}
