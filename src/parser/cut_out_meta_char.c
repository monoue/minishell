/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_out_meta_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:09 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 16:02:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_out_meta_char(const char *str, size_t *index)
{
	const size_t start = *index;

	(*index)++;
	return (ft_strndup(&str[start], 1));
}
