/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:21:27 by monoue            #+#    #+#             */
/*   Updated: 2021/02/10 09:54:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin_free(char *s1, const char *s2, size_t n)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strnjoin(s1, s2, n);
	free(tmp);
	return (s1);
}
