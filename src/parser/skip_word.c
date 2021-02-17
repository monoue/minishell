/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:15 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:25:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_word(const char *str, size_t *index)
{
	const size_t len = ft_strlen(str);

	while (*index < len && !((is_quote_char(str[*index])
								|| is_metachar(str[*index])
								|| is_space_or_tab(str[*index]))
								&& !is_escaped(str, *index)))
		(*index)++;
}
