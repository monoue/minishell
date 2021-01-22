/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:47:27 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:20:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int num)
{
	if (num >= 10)
		return (ft_strjoin_free_both(ft_utoa(num / 10), ft_utoa(num % 10)));
	else
		return (ft_ctoa((char)ITOC(num)));
}
