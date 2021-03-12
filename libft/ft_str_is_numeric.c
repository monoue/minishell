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
	const size_t	len = ft_strlen(str);
	size_t			index;

	index = 0;
	while (index < len && ft_isdigit(str[index]))
		index++;
	return (index == len);
}
