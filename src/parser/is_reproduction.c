/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reproduction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:35 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 22:56:32 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_reproduction(char *word)
{
	const char	*reproductions[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
	};
	size_t		index;
	char		*continuous_quotes_trimmed_str;

	continuous_quotes_trimmed_str = get_continuous_quotes_trimmed_str(word);
	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(continuous_quotes_trimmed_str, reproductions[index]))
		{
			SAFE_FREE(continuous_quotes_trimmed_str);
			return (true);
		}
		index++;
	}
	SAFE_FREE(continuous_quotes_trimmed_str);
	return (false);
}
