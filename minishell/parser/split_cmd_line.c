#include "../minishell.h"

static size_t	get_ret_s_len(const char *str, size_t *index)
{
	const size_t	start = *index;
	size_t			quotes_sets_num;
	char			quote;

	quotes_sets_num = 0;
	while (str[*index] != '\0' && str[*index] != ' ' && !is_redirection(str[*index]))
	{
		if (is_quote(str[*index]))
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
			while (str[*index] != '\0' && !is_quote(str[*index]) && !is_redirection(str[*index]) && str[*index] != ' ')
				(*index)++;
		}
	}
	return (*index - start - quotes_sets_num * 2);
}

static char		*cut_out_one_word(const char *str, size_t *index)
{
	const size_t	start = *index;
	char			*ret_s;
	size_t			src_i;
	size_t			dst_i;

	ret_s = ft_calloc((get_ret_s_len(str, index) + 1), sizeof(char));
	if (!ret_s)
		return (NULL);
	src_i = start;
	dst_i = 0;
	while (src_i < *index)
	{
		if (is_quote(str[src_i]))
		{
			src_i++;
			continue ;
		}
		ret_s[dst_i] = str[src_i];
		dst_i++;
		src_i++;
	}
	return (ret_s);
}

static char		*cut_out_one_elem(const char *str, size_t *index)
{
	size_t	start;

	while (str[*index] && str[*index] == ' ')
		(*index)++;
	start = *index;
	if (is_redirection(str[*index]))
	{
		(*index)++;
		if (str[*index] == '>')	
			(*index)++;
		return (ft_substr(str, start, *index - start))	;
	}
	return (cut_out_one_word(str, index));
}

char			**split_cmd_line(char const *str)
{
	char	**words;
	size_t	words_num;
	size_t	index;
	size_t	w_i;

	if (!str)
		return (NULL);
	words_num = count_cmd_line_words(str);
	words = malloc(sizeof(*words) * (words_num + 1));
	if (!words)
		return (NULL);
	w_i = 0;
	index = 0;
	while (w_i < words_num)
	{
		words[w_i] = cut_out_one_elem(str, &index);
		if (!words[w_i])
		{
			ft_free_split(words);
			return (NULL);
		}
		w_i++;
	}
	words[w_i] = NULL;
	return (words);
}
