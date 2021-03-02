/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 09:51:28 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_dollar_bis(char *line, int *i, char *tmp)
{
	if (line[*i] == '$')
	{
		SAFE_FREE(tmp);
		(*i)++;
		return (tmp = ft_strdup("(process ID)"));
	}
	if (line[*i] == '?')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
		return (tmp);
	}
	return (tmp);
}

void	check_escape(const char *str, int *index, int *len)
{
	if (str[*index] == '\\')
		(*index)++;
	while (*index < *len && str[*index] != '\\')
		(*index)++;
}

bool	check_is_escape(const char *str, int index)
{
	if (str[index] == '\\' && str[index + 1] != '\''
		&& (str[index + 1] == '\"' || str[index + 1] == '$'
		|| str[index + 1] == '\\'))
		return (true);
	return (false);
}
