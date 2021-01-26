/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_format_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 12:52:06 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 13:49:07 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_format_info.h"

void	init_format_info(t_format_info *info)
{
	info->min_width = NOT_SET;
	info->minus = false;
	info->zero = false;
	info->precision = NOT_SET;
	info->c_null = false;
	info->value = NULL;
}
