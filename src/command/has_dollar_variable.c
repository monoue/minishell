/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_dollar_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:14:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/09 08:04:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool				has_dollar_variable(char *arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '$' && ((arg[i - 1] != '\\' ||
			(arg[i - 1] == '\\' && arg[i - 2] == '\\')) && arg[i + 1] != '\0'))
			return (true);
		i++;
	}
	return (false);
}
