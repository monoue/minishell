/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_char_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 08:24:54 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	head_char_equal(const char *str, char c)
{
	if (!str)
		return (false);
	return (str[0] == c);
}
