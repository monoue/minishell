/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_words.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:09 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 14:32:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_ret_s_len(const char *str, size_t *index)
{
	const size_t	start = *index;

	skip_chunk(str, index);
	return (*index - start);
}

static char		*cut_out_one_word(const char *str, size_t *index)
{
	const size_t	start = *index;
	const size_t	len = get_ret_s_len(str, index);

	return (ft_strndup(&str[start], len));
}

static char		*cut_out_redirection(const char *str, size_t *index)
{
	const size_t start = *index;

	skip_redirection(str, index);
	return (ft_strndup(&str[start], *index - start));
}

static char		*cut_out_meta_char(const char *str, size_t *index)
{
	const size_t start = *index;

	(*index)++;
	return (ft_strndup(&str[start], 1));
}

static char		*cut_out_one_elem(const char *str, size_t *index)
{
	skip_spaces(str, index);
	if (is_redirection_str_partial(&str[*index]))
		return (cut_out_redirection(str, index));
	else if (is_specific_char_not_escaped(str, *index, is_metachar))
		return (cut_out_meta_char(str, index));
	return (cut_out_one_word(str, index));
}

void			set_words(const char *str, char **words, size_t words_num)
{
	size_t	w_i;
	size_t	index;

	w_i = 0;
	index = 0;
	// DS(str);
	while (w_i < words_num)
	{
		words[w_i] = cut_out_one_elem(str, &index);
		if (!words[w_i])
		{
			ft_free_split(words);
			exit_err_msg(MALLOC_ERR);
		}
		w_i++;
	}
	words[w_i] = NULL;
}
