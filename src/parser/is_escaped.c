/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_escaped.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:24:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_escaped(const char *str, size_t index)
{
	size_t	b_slash_num;
	int		i;

	if (index == 0)
		return (false);
	i = index - 1;
	b_slash_num = 0;
	while (i >= 0 && str[i] == '\\')
	{
		b_slash_num++;
		i--;
	}
	return (b_slash_num % 2);
}
