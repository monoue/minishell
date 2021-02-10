// #include "../minishell.h"

// static size_t	get_ret_s_len(const char *str, size_t *index)
// {
// 	const size_t	len = ft_strlen(str);
// 	const size_t	start = *index;
// 	size_t			quotes_sets_num;
// 	char			quote;

// 	quotes_sets_num = 0;
// 	// ここが問題。direction の場合、区切る要素が違う。redirection でしか区切らない。
// 	while (*index < len && !((is_space_or_tab(str[*index]) || is_redirection_char(str[*index])) && !is_escaped(str, *index)))
// 	{
// 		if (is_specific_char_not_escaped(str, *index, is_quote_char))
// 		{
// 			skip_quotes(str, index);
// 			quotes_sets_num++;
// 		}
// 		else
// 		{
// 			while (*index < len && !((is_quote_char(str[*index]) || is_redirection_char(str[*index]) || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
// 				(*index)++;
// 		}
// 	}
// 	return (*index - start - quotes_sets_num * 2);
// }

// // これが未改修だった
// static char		*cut_out_one_word(const char *str, size_t *index)
// {
// 	const size_t	start = *index;
// 	char			*ret_s;
// 	size_t			src_i;
// 	size_t			dst_i;

// 	ret_s = ft_calloc((get_ret_s_len(str, index) + 1), sizeof(char));
// 	if (!ret_s)
// 		return (NULL);
// 	// ここを strnjoin で書き換える
// 	src_i = start;
// 	dst_i = 0;
// 	while (src_i < *index)
// 	{
// 		if (is_quote_char(str[src_i]))
// 		{
// 			src_i++;
// 			continue ;
// 		}
// 		ret_s[dst_i] = str[src_i];
// 		dst_i++;
// 		src_i++;
// 	}
// 	return (ret_s);
// }

// static char		*cut_out_one_elem(const char *str, size_t *index)
// {
// 	while (str[*index] && is_specific_char_not_escaped(str, *index, is_space_or_tab))
// 		(*index)++;
// 	if (is_redirection_char(str[*index]))
// 		return (cut_out_meta_element(str, index));
// 	return (cut_out_one_word(str, index));
// }

// char			**split_by_direction(char const *str)
// {
// 	char	**words;
// 	size_t	words_num;
// 	size_t	index;
// 	size_t	w_i;

// 	if (!str)
// 		return (NULL);
// 	words_num = count_command_argv(str);
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
