/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:50:34 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 22:59:51 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, const int c)
{
	const unsigned char	uc = (unsigned char)c;
	const size_t		s_len_including_null = ft_strlen(s) + 1;
	size_t				index;

	index = 0;
	if (s == 0)
		return (NULL);
	while (index < s_len_including_null)
	{
		if (s[index] == uc)
			return ((char *)&s[index]);
		index++;
	}
	return (NULL);
}
