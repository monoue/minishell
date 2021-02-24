/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_command_line_words.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:53 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 15:41:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		skip_spaces(const char *str, size_t *index)
{
	const size_t	len = ft_strlen(str);

	while (*index < len && is_specific_char_not_escaped(str, *index,
															is_space_or_tab))
		(*index)++;
}

size_t		count_command_line_words(char const *str)
{
	size_t			index;
	size_t			words_num;
	const size_t	len = ft_strlen(str);

	index = 0;
	skip_spaces(str, &index);
	words_num = 0;
	while (index < len)
	{
		if (is_redirection_str_partial(&str[index]))
			skip_redirection(str, &index);
		else if (is_specific_char_not_escaped(str, index, is_metachar))
			index++;
		else
			skip_chunk(str, &index);
		skip_spaces(str, &index);
		words_num++;
	}
	return (words_num);
}
