/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reproduction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:35 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 06:39:42 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_reproduction(char *word)
{
	const char		*reproductions[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
	};
	const size_t	reproductions_num = ft_count_strs(reproductions);
	size_t			index;
	char			*continuous_quotes_trimmed_str;

	continuous_quotes_trimmed_str = get_continuous_quotes_trimmed_str(word);
	index = 0;
	while (index < reproductions_num)
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
