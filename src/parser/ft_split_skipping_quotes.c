/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_skipping_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:04:52 by monoue            #+#    #+#             */
/*   Updated: 2021/02/10 12:23:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_words(char const *str, char sep_c)
{
	size_t			index;
	size_t			words_num;
	const size_t	len = ft_strlen(str);

	index = 0;
	while (index < len && str[index] == sep_c)
		index++;
	words_num = 0;
	while (index < len)
	{
		while (index < len && !(str[index] == sep_c && !is_escaped(str, index)))
		{
			if (is_specific_char_not_escaped(str, index, is_quote_char))
				skip_quotes(str, &index);
			else
				index++;
		}
		words_num++;
		while (index < len && (str[index] == sep_c && !is_escaped(str, index)))
			index++;
	}
	return (words_num);
}

static char		**return_null_freeing_all(char **arr, size_t end)
{
	size_t	index;

	index = 0;
	while (index < end)
	{
		SAFE_FREE(arr[index]);
		index++;
	}
	SAFE_FREE(arr);
	return (NULL);
}

static char		*cut_out_one_word(const char *str, char sep_c, size_t *index)
{
	size_t			start;
	const size_t	s_len = ft_strlen(str);

	while (*index < s_len && str[*index] == sep_c
				&& !is_specific_char_not_escaped(str, *index, is_quote_char))
		(*index)++;
	start = *index;
	while (*index < s_len
			&& !(str[*index] == sep_c && !is_escaped(str, *index)))
	{
		if (is_specific_char_not_escaped(str, *index, is_quote_char))
			skip_quotes(str, index);
		else
			(*index)++;
	}
	return (ft_strndup(&str[start], *index - start));
}

char			**ft_split_skipping_quotes(char const *str, char sep_c)
{
	char	**words;
	size_t	words_num;
	size_t	index;
	size_t	w_i;

	if (str == NULL)
		return (NULL);
	words_num = count_words(str, sep_c);
	words = ft_calloc((words_num + 1), sizeof(*words));
	if (words == NULL)
		return (NULL);
	if (sep_c == '\0')
		return (words);
	w_i = 0;
	index = 0;
	while (w_i < words_num)
	{
		words[w_i] = cut_out_one_word(str, sep_c, &index);
		if (words[w_i] == NULL)
			return (return_null_freeing_all(words, w_i));
		w_i++;
	}
	return (words);
}
