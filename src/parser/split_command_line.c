/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:18 by monoue            #+#    #+#             */
/*   Updated: 2021/02/22 09:35:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_command_line_with_quotes(char const *str)
{
	char	**words;
	size_t	words_num;

	if (!str)
		return (NULL);
	words_num = count_command_line_words(str);
	words = malloc(sizeof(*words) * (words_num + 1));
	if (!words)
		exit_err_msg(MALLOC_ERR);
	set_words(str, words, words_num);
	return (words);
}

static bool	str_has_env(const char *str)
{
	char	*tmp;
	char	target;

	tmp = ft_strchr(str, '$');
	if (!tmp || ft_strlen(tmp) < 3)
		return (false);
	target = tmp[1];
	if (is_quote_char(target) || is_space_or_tab(target))
		return (false);
	return (true);
}

// TODO: こいつを改良する。クオーテーション単位で実行されるようにする。
// static void	trim_quotes_if_not_env(char **words)
// {
// 	size_t	index;

// 	index = 0;
// 	while (words[index])
// 	{
// 		if (str_is_quoted(words[index]) && !str_has_env(words[index]))
// 			words[index] = ft_substr_free(words[index], 1,
// 												ft_strlen(words[index]) - 2);
// 		index++;
// 	}
// }

static void	trim_quotes_if_not_env(char **words)
{
	size_t	w_i;


	char	*word;
	size_t	w_len;
	size_t	index;
	char	*ret_s;
	size_t	start;
	char	*quoted_str;
	char	*tmp;


	w_i = 0;
	while (words[w_i])
	{
		word = words[w_i];
		w_len = ft_strlen(word);
		index = 0;
		ret_s = ft_strdup("");
		if (!ret_s)
			exit_err_msg(MALLOC_ERR);
		while (index < w_len)
		{
			start = index;
			if (!is_specific_char_not_escaped(word, index, is_quote_char))
			{
				while (index < w_len && !is_specific_char_not_escaped(word, index, is_quote_char))
					index++;
				ret_s = ft_strnjoin_free(ret_s, &word[start], index - start);
			}
			else
			{
				skip_quotes(word, &index);
				quoted_str = ft_strndup(&word[start], index - start);
				if (str_has_env(quoted_str))
					ret_s = ft_strjoin_free_both(ret_s, quoted_str);
				else
				{
					ret_s = ft_strnjoin_free(ret_s, &quoted_str[1], ft_strlen(quoted_str) - 2);
					SAFE_FREE(quoted_str);
				}
			}
		}
		SAFE_FREE(words[w_i]);
		words[w_i] = ft_strdup_free(ret_s);
		w_i++;
	}
}

char        **split_command_line(char const *str)
{
    char    **words;
    char    *tmp;
    char    **ret_words;

    tmp = turn_dollar_question_into_value(str);
    words = split_command_line_with_quotes(tmp);
    free(tmp);
    if (!words)
        return (NULL);
    trim_quotes_if_not_env(words);
    return (words);
}
