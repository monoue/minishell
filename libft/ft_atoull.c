/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:06 by monoue            #+#    #+#             */
/*   Updated: 2021/03/03 08:18:17 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoull(const char *str)
{
	size_t				index;
	unsigned long long	n;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+')
		index++;
	n = 0;
	while (ft_isdigit(str[index]))
	{
		n = n * 10 + (str[index] - '0');
		index++;
	}
	return (n);
}
