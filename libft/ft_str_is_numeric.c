/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 10:27:33 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 22:38:05 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_is_numeric(const char *str)
{
	size_t	index;
	size_t	i;
	size_t	length;

	index = 0;
	i = 0;
	length = ft_strlen(str);
	length--;
	while (str[length] == ' ')
	{
		i++;
		length--;
	}
	while (str[index] != '\0' && ft_isdigit(str[index]) && str[index] != ' ')
	{
		if (str[index] != ' ')
			index++;
	}
	return (index == ft_strlen(str) - i);
}
