/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:19:29 by monoue            #+#    #+#             */
/*   Updated: 2021/02/12 13:25:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char const *str, size_t *index)
{
	char			quote;
	const size_t	len = ft_strlen(str);

	quote = str[*index];
	(*index)++;
	while (*index < len && !(str[*index] == quote && !is_escaped(str, *index)))
		(*index)++;
	(*index)++;
}
