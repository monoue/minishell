/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:04:52 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 14:29:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char sep_c)
{
	size_t	index;
	size_t	words_num;

	index = 0;
	while (str[index] != '\0' && str[index] == sep_c)
		index++;
	words_num = 0;
	while (str[index] != '\0')
	{
		while (str[index] != '\0' && str[index] != sep_c)
			index++;
		words_num++;
		while (str[index] != '\0' && str[index] == sep_c)
			index++;
	}
	return (words_num);
}

static char		**return_null_freeing_all(char **arr, int i)
{
	int	index;

	index = i;
	while (index >= 0)
	{
		SAFE_FREE(arr[index]);
		index--;
	}
	SAFE_FREE(arr);
	return (NULL);
}

static char		*cut_out_one_word(const char *str, char sep_c, size_t *index)
{
	size_t			start;
	const size_t	s_len = ft_strlen(str);

	while (*index < s_len && str[*index] == sep_c)
		(*index)++;
	start = *index;
	while (*index < s_len && str[*index] != sep_c)
		(*index)++;
	return (ft_substr(str, start, *index - start));
}

char			**ft_split(char const *str, char sep_c)
{
	char	**words;
	size_t	words_num;
	size_t	index;
	int		w_i;

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
	while (w_i < (int)words_num)
	{
		words[w_i] = cut_out_one_word(str, sep_c, &index);
		if (words[w_i] == NULL)
			return (return_null_freeing_all(words, w_i - 1));
		w_i++;
	}
	return (words);
}
