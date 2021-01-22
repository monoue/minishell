/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:08:33 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 13:16:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_with_zero.h"

void	fill_output_with_zero(char **str, int margin)
{
	while (margin)
	{
		*str = ft_strjoin_free_both(ft_ctoa('0'), *str);
		margin--;
	}
}

void	fill_empty_with_zero(char **str, int margin, t_format_info *info)
{
	if (info->minus == true && info->precision == NOT_SET)
	{
		while (margin)
		{
			*str = ft_strjoin_free_both(*str, ft_ctoa('0'));
			margin--;
		}
	}
	else
	{
		while (margin)
		{
			*str = ft_strjoin_free_both(ft_ctoa('0'), *str);
			margin--;
		}
	}
}
