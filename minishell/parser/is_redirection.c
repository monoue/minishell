/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:24:05 by monoue            #+#    #+#             */
/*   Updated: 2021/02/02 09:00:23 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection_char(char c)
{
	// return (ft_strchr("><|", c));
	return (ft_strchr("><", c));
}

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
