/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:00:02 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:07:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_xtoa_printf.h"

char	*ft_xtoa_printf(unsigned long long num, char conv_c)
{
	if (num >= 16)
		return (ft_strjoin_free_both(ft_xtoa_printf(num / 16, conv_c),
									ft_xtoa_printf(num % 16, conv_c)));
	else if (conv_c == 'X')
		return (ft_ctoa("0123456789ABCDEF"[num]));
	else
		return (ft_ctoa("0123456789abcdef"[num]));
}
