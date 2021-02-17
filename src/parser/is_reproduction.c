/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reproduction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:35 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:25:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_reproduction(char *word)
{
	const char	*reproductions[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	size_t		index;

	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(word, reproductions[index]))
			return (true);
		index++;
	}
	return (false);
}
