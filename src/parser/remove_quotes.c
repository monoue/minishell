#include "../minishell.h"

static size_t	get_ret_s_len(const char *str, size_t *index)
{
	size_t			quotes_sets_num;
	char			quote;

	quotes_sets_num = 0;
	while (str[*index] != '\0' && !((is_space_or_tab(str[*index]) || is_metachar(str[*index])) && !is_escaped(str, *index)))
	{
		if (is_specific_char_not_escaped(str, *index, is_quote_char))
		{
			quote = str[*index];
			(*index)++;
			while (str[*index] != quote)
				(*index)++;
			(*index)++;
			quotes_sets_num++;
		}
		else
		{
			while (str[*index] != '\0' && !((is_quote_char(str[*index]) || is_metachar(str[*index]) || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
				(*index)++;
		}
	}
	return (*index - quotes_sets_num * 2);
}

static void		set_word(const char *str, size_t slen, char **container)
{
	size_t	src_i;
	size_t	dst_i;
	char	quote;

	src_i = 0;
	dst_i = 0;
	while (src_i < slen)
	{
		if (is_specific_char_not_escaped(str, src_i, is_quote_char))
		{
			quote = str[src_i];
			src_i++;
			while (src_i < slen && str[src_i] != quote)
			{
				(*container)[dst_i] = str[src_i];
				dst_i++;
				src_i++;
			}
			src_i++;
			continue ;
		}
		(*container)[dst_i] = str[src_i];
		dst_i++;
		src_i++;
	}
}

char		*remove_quotes(const char *str)
{
	char	*ret_s;
	size_t	index;

	index = 0;
	ret_s = ft_calloc((get_ret_s_len(str, &index) + 1), sizeof(char));
	if (!ret_s)
		return (NULL);
	set_word(str, index, &ret_s);
	return (ret_s);
}

// static char		*cut_out_one_elem(const char *str, size_t *index)
// {
// 	size_t	start;

// 	while (str[*index] && is_space_or_tab(str[*index]))
// 		(*index)++;
// 	start = *index;
// 	if (is_metachar(str[*index]))
// 	{
// 		if (ft_strnequal(&str[*index], ">>", 2))
// 			*index += 2;
// 		else
// 			(*index)++;
// 		return (ft_substr(str, start, *index - start));
// 	}
// 	return (cut_out_one_word(str, index));
// }

// char		**split_command_line(char const *str)
// {
// 	char	**words;
// 	size_t	words_num;
// 	size_t	index;
// 	size_t	w_i;

// 	if (!str)
// 		return (NULL);
// 	words_num = count_command_line_words(str);
// 	words = malloc(sizeof(*words) * (words_num + 1));
// 	if (!words)
// 		return (NULL);
// 	w_i = 0;
// 	index = 0;
// 	while (w_i < words_num)
// 	{
// 		words[w_i] = cut_out_one_elem(str, &index);
// 		if (!words[w_i])
// 		{
// 			ft_free_split(words);
// 			return (NULL);
// 		}
// 		w_i++;
// 	}
// 	words[w_i] = NULL;
// 	return (words);
// }
