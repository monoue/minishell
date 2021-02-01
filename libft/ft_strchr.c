/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:50:34 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:03:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	uc = (unsigned char)c;
	const size_t		s_len_including_null = ft_strlen(s) + 1;
	size_t				index;

	index = 0;
	while (index < s_len_including_null)
	{
		if (s[index] == uc)
			return ((char *)&s[index]);
		index++;
	}
	return (NULL);
}
