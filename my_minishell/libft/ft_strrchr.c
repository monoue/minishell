/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:50:34 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:07:07 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	uc = c;
	const int			s_len = (int)ft_strlen(s);
	int					index;

	if (s == NULL)
		return (NULL);
	index = s_len;
	while (index >= 0)
	{
		if (s[index] == uc)
			return ((char *)&s[index]);
		index--;
	}
	return (NULL);
}
