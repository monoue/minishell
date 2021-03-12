/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 14:06:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_dollar_bis(char *line, int *i, char *tmp)
{
	if (line[*i] == '$')
	{
		SAFE_FREE(tmp);
		(*i)++;
		return (tmp = ft_strdup("(processID)"));
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
		|| str[index + 1] == '\\' || str[index + 1] == '`'))
		return (true);
	return (false);
}

int		check_quote(int a, char *line)
{
	int	b;

	b = 0;
	while (line[a])
	{
		if (line[a] == '\'')
			b++;
		a++;
	}
	return (b);
}
