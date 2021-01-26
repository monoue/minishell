/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:27:09 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 08:52:24 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	size_t				index;

	if (dst == src)
		return (dst);
	d = dst;
	index = 0;
	while (index < n)
	{
		d[index] = s[index];
		if (s[index] == (unsigned char)c)
			return (&dst[index + 1]);
		index++;
	}
	return (NULL);
}
