#include "../minishell.h"

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

char			*cut_out_meta_element(const char *str, size_t *index)
{
	const size_t start = *index;

	if (ft_strnequal(&str[*index], ">>", 2))
		*index += 2;
	else
		(*index)++;
	return (ft_strndup(&str[start], *index - start));
}

char		*cut_out_one_elem(const char *str, size_t *index)
{
	while (str[*index] && is_specific_char_not_escaped(str, *index, is_space_or_tab))
		(*index)++;
	if (is_specific_char_not_escaped(str, *index, is_metachar))
		return (cut_out_meta_element(str, index));
	return (cut_out_one_word(str, index));
}

static void	set_words(const char *str, char **words, size_t words_num)
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

char		**split_command_line_with_quotes(char const *str)
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

bool	str_is_quoted(const char *str)
{
	const size_t	len = ft_strlen(str);

	if (len < 2)
		return (false);
	return (is_quote_char(str[0]) && str[0] == str[len - 1]);
}

bool	str_has_env(const char *str)
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

static void	trim_quotes(char **words, size_t index)
{
	char	*tmp;

	tmp = words[index];
	words[index] = ft_strndup((&tmp[1]), ft_strlen(tmp) - 2);
	free(tmp);
}

static void	trim_quotes_if_not_env(char **words)
{
	size_t	index;

	index = 0;
	while (words[index])
	{
		if (str_is_quoted(words[index]) && !str_has_env(words[index]))
			trim_quotes(words, index);
		index++;
	}
}

char		**split_command_line(char const *str)
{
	char	**words;

	words = split_command_line_with_quotes(str);
	if (!words)
		return (NULL);
	trim_quotes_if_not_env(words);
	return (words);
}
