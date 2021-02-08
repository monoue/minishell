/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:24:05 by monoue            #+#    #+#             */
/*   Updated: 2021/02/04 10:50:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection_str(char *str)
{
	const char	*redirections[] = {
		">",
		">>",
		"<",
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
