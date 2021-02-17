/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specific_char_not_escaped.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:39 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:25:40 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_specific_char_not_escaped(const char *str, size_t index,
															bool (*func)(char))
{
	if (!func(str[index]))
		return (false);
	return (!is_escaped(str, index));
}
