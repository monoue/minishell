/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:36:02 by monoue            #+#    #+#             */
/*   Updated: 2021/02/11 13:39:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_is_quoted(const char *str)
{
	const size_t len = ft_strlen(str);

	if (len < 2)
		return (false);
	return (is_quote_char(str[0]) && str[0] == str[len - 1]);
}

bool	str_is_quoted_by_single(const char *str)
{
	const size_t len = ft_strlen(str);

	if (len < 2)
		return (false);
	return (is_quote_char(str[0]) && str[0] == str[len - 1]);
}
