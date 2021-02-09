#include "../minishell.h"

static size_t	get_ret_s_len(const char *str, size_t *index)
{
	const size_t	start = *index;
	const size_t	len = ft_strlen(str);
	char			quote;

		if (is_specific_char_not_escaped(str, *index, is_quote_char))
		{
			quote = str[*index];
			(*index)++;
			while (!(str[*index] == quote && !is_escaped(str, *index)))
				(*index)++;
			(*index)++;
		}
		else
		{
			while (*index < len && !((is_quote_char(str[*index]) || is_metachar(str[*index]) || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
				(*index)++;
		}
	return (*index - start);
}

static char		*cut_out_one_word(const char *str, size_t *index)
{
	const size_t	start = *index;
	size_t	len;

	len = get_ret_s_len(str, index);
	return (ft_strndup(&str[start], len));
}

static char		*cut_out_one_elem(const char *str, size_t *index)
{
	size_t	start;

	while (str[*index] && is_specific_char_not_escaped(str, *index, is_space_or_tab))
		(*index)++;
	start = *index;
	if (is_specific_char_not_escaped(str, *index, is_metachar))
	{
		if (ft_strnequal(&str[*index], ">>", 2))
			*index += 2;
		else
			(*index)++;
		return (ft_substr(str, start, *index - start));
	}
	return (cut_out_one_word(str, index));
}

char		**split_command_line(char const *str)
{
	char	**words;
	size_t	words_num;
	size_t	index;
	size_t	w_i;

	if (!str)
		return (NULL);
	words_num = count_command_line_words(str);
	words = malloc(sizeof(*words) * (words_num + 1));
	if (!words)
		exit_err_msg(MALLOC_ERR);
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
