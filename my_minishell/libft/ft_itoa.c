/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:39:21 by monoue            #+#    #+#             */
/*   Updated: 2020/07/02 11:24:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_letters(long n)
{
	size_t	count;
	long	d;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	d = 1;
	while (n >= d * 10)
	{
		d *= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*p;
	long	n2;
	long	d;
	int		i;

	if (!(p = malloc((ft_count_letters(n) + 1) * sizeof(*p))))
		return (NULL);
	i = 0;
	if (n < 0)
	{
		p[0] = '-';
		i++;
	}
	d = 1;
	n2 = n < 0 ? -1 * (long)n : (long)n;
	while (n2 >= d * 10)
		d *= 10;
	while (d > 0)
	{
		p[i++] = ft_itoc(n2 / d);
		n2 %= d;
		d /= 10;
	}
	p[i] = '\0';
	return (p);
}
