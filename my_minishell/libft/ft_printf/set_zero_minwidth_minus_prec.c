/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_zero_minwidth_minus_prec.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:09:36 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 13:47:05 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_zero_minwidth_minus_prec.h"

static int	minwidth_o_prec_to_int(char *target, int *index)
{
	int	num;

	num = 0;
	while (ft_isdigit(target[*index]))
	{
		num = num * 10 + CTOI(target[*index]);
		(*index)++;
	}
	return (num);
}

static void	get_index_when_prec_invalid(char *target, int *index)
{
	(*index)++;
	while (ft_isdigit(target[*index]))
		(*index)++;
}

void		set_zero_minwidth_minus_prec(char *target, int *index,
t_format_info *info)
{
	if (target[*index] == '0')
		info->zero = true;
	if (ft_isdigit(target[*index]))
		info->min_width = minwidth_o_prec_to_int(target, index);
	if (target[*index] == '-')
	{
		info->minus = true;
		(*index)++;
	}
	if (target[*index] == '.')
	{
		(*index)++;
		if (target[*index] == '-')
			get_index_when_prec_invalid(target, index);
		else
			info->precision = minwidth_o_prec_to_int(target, index);
	}
}
