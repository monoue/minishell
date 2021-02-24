/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:24:05 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 15:57:12 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection_str(const char *str)
{
	const char	*redirections[] = {
		">",
		">>",
		"<",
		NULL
	};
	size_t		r_i;
	size_t		s_i;

	if (ft_str_is_numeric(str))
		return (false);
	s_i = 0;
	while (ft_isdigit(str[s_i]))
		s_i++;
	r_i = 0;
	while (redirections[r_i])
	{
		if (ft_strequal(&str[s_i], redirections[r_i]))
			return (true);
		r_i++;
	}
	return (false);
}

bool	is_redirection_str_partial(const char *str)
{
	const char	*redirections[] = {
		">>",
		">",
		"<",
		NULL
	};
	size_t		r_i;
	size_t		s_i;

	if (ft_str_is_numeric(str))
		return (false);
	s_i = 0;
	while (ft_isdigit(str[s_i]))
		s_i++;
	r_i = 0;
	while (redirections[r_i])
	{
		if (ft_strnequal(&str[s_i], redirections[r_i],
												ft_strlen(redirections[r_i])))
		{
			return (true);
		}
		r_i++;
	}
	return (false);
}

bool	is_pipe_or_break_str(char *str)
{
	const char	*redirections[] = {
		"|",
		";",
		NULL
	};
	size_t		index;

	index = 0;
	while (redirections[index])
	{
		if (ft_strequal(str, redirections[index]))
			return (true);
		index++;
	}
	return (false);
}

bool	is_metachar_str(char *str)
{
	return (is_redirection_str(str) || is_pipe_or_break_str(str));
}
