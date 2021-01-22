/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:35:57 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:27:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	s_len;
	size_t	index;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	p = malloc((sizeof(*p)) * (s_len + 1));
	if (p == NULL)
		return (NULL);
	index = 0;
	while (index < s_len)
	{
		p[index] = f(index, s[index]);
		index++;
	}
	p[index] = '\0';
	return (p);
}
