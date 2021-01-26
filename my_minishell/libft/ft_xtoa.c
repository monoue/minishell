/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:22:04 by monoue            #+#    #+#             */
/*   Updated: 2020/10/22 10:32:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xtoa(unsigned num)
{
	if (num >= 16)
		return (ft_strjoin_free_both(ft_xtoa(num / 16), ft_xtoa(num % 16)));
	return (ft_ctoa("0123456789abcdef"[num]));
}
