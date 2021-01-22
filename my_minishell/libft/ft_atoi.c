/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:06 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 13:36:15 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	bool			is_signed;
	unsigned int	i;
	long			n;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	is_signed = false;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_signed = true;
		i++;
	}
	n = 0;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (is_signed ? (int)-n : (int)n);
}
