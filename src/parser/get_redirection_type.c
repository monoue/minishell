/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:38 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 07:07:51 by monoue           ###   ########.fr       */
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
	size_t							r_i;
	size_t							e_i;

	e_i = 0;
	while (ft_isdigit(element[e_i]))
		e_i++;
	r_i = 0;
	while (r_i < TYPES_NUM)
	{
		comb = combs[r_i];
		if (ft_strequal(&element[e_i], comb.symbol))
			return (comb.type);
		r_i++;
	}
	return (ERROR);
}
