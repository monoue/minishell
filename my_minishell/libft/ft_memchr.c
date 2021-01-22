/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:22:57 by monoue            #+#    #+#             */
/*   Updated: 2020/10/15 16:01:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str = s;
	size_t		index;

	index = 0;
	while (index < n)
	{
		if (str[index] == (char)c)
			return ((void *)&str[index]);
		index++;
	}
	return (NULL);
}
