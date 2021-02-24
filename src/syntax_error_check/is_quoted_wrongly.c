/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted_wrongly.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:57:45 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 14:17:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quoted_wrongly(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;

	index = 0;
	while (index < len)
	{
		if (is_specific_char_not_escaped(str, index, is_quote_char))
		{
			skip_quotes(str, &index);
			if (index == len + 1)
				return (true);
		}
		else
			index++;
	}
	return (false);
}
