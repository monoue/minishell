/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:54:49 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 10:50:05 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_is_of_tabs_or_spaces(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;

	index = 0;
	while (str[index] == ' ' || str[index] == '\t')
		index++;
	return (index == len);
}
