/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:38 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:24:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection_type(char *element)
{
	const t_redirection_combination combs[] = {
		{">", TYPE_OUTPUT},
		{">>", TYPE_APPEND},
		{"<", TYPE_INPUT},
	};
	t_redirection_combination		comb;
	size_t							index;

	index = 0;
	while (index < TYPES_NUM)
	{
		comb = combs[index];
		if (ft_strequal(element, comb.symbol))
			return (comb.type);
		index++;
	}
	return (ERROR);
}
