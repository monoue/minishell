/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_num_is_over_llong_max.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:05 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/01 14:46:54 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		digits_num_is_over_llong_max(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] == '0')
		index++;
	return (ft_strlen(&str[index]) > LLONG_MAX_DIGITS);
}
