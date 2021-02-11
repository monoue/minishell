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

static char		*cut_out_meta_element(const char *str, size_t *index)
{
	const size_t start = *index;

	if (ft_strnequal(&str[*index], ">>", 2))
		*index += 2;
	else
		(*index)++;
	return (ft_strndup(&str[start], *index - start));
}

static char		*cut_out_one_elem(const char *str, size_t *index)
{
	while (str[*index] && is_specific_char_not_escaped(str, *index,
															is_space_or_tab))
		(*index)++;
	if (is_specific_char_not_escaped(str, *index, is_metachar))
		return (cut_out_meta_element(str, index));
	return (cut_out_one_word(str, index));
}

void			set_words(const char *str, char **words, size_t words_num)
{
	size_t	w_i;
	size_t	index;

	w_i = 0;
	index = 0;
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
