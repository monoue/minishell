/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted_wrongly.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:55:41 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 15:56:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted_wrongly(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	char			quote;

	index = 0;
	while (index < len)
	{
		if (is_specific_char_not_escaped(str, index, is_quote_char))
		{
			quote = str[index];
			index++;
			while (index < len
						&& !(str[index] == quote && !is_escaped(str, index)))
			{
				index++;
			}
			if (index == len)
				return (true);
		}
		index++;
	}
	return (false);
}
