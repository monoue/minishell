/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:19:29 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 14:17:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char const *str, size_t *index)
{
	char			quote;
	const size_t	len = ft_strlen(str);

	quote = str[*index];
	(*index)++;
	if (quote == '\'')
	{
		while (*index < len && str[*index] != quote)
			(*index)++;
	}
	else
	{
		while (*index < len && !(str[*index] == quote && !is_escaped(str, *index)))
			(*index)++;
	}
	(*index)++;
}

void	skip_redirection(const char *str, size_t *index)
{
	while (ft_isdigit(str[*index]))
		(*index)++;
	if (ft_strnequal(&str[*index], ">>", 2))
		*index += 2;
	else
		(*index)++;
}
