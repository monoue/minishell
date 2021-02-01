/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_margin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:06:58 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:10:14 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "apply_margin.h"

static void	fill_empty_width(char filler, char ***new_target,
					int empty_width, t_format_info *info)
{
	if (info->minus)
	{
		while (**new_target && empty_width--)
			**new_target = ft_strjoin_free_both(**new_target,
												ft_ctoa(filler));
	}
	else
	{
		while (**new_target && empty_width--)
			**new_target = ft_strjoin_free_both(ft_ctoa(filler),
															**new_target);
	}
}

void		apply_margin(char **new_target, int empty_width,
														t_format_info *info)
{
	if (info->minus)
		fill_empty_width(' ', &new_target, empty_width, info);
	else if (info->zero && info->precision == NOT_SET && *new_target[0]
	&& *new_target[0] == '-')
	{
		*new_target[0] = '0';
		fill_empty_width('0', &new_target, empty_width, info);
		*new_target[0] = '-';
	}
	else if (info->precision != NOT_SET || info->zero == false)
		fill_empty_width(' ', &new_target, empty_width, info);
	else
		fill_empty_width('0', &new_target, empty_width, info);
}
