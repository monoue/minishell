/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:50:34 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 07:28:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	const size_t	s_len = ft_strlen(dest);
	const size_t	srclen = ft_strlen(src);

	if (destsize < s_len + 1)
		return (srclen + destsize);
	ft_strlcpy(&dest[s_len], src, destsize - s_len);
	return (srclen + s_len);
}
