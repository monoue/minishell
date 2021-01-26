/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:47:27 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 08:57:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	int					index;

	if (src >= dst)
		return (ft_memcpy(dst, src, len));
	d = dst;
	index = (int)len - 1;
	while (index >= 0)
	{
		d[index] = s[index];
		index--;
	}
	return (dst);
}
