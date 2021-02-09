#include "../minishell.h"

static size_t	get_ret_s_len(const char *str, size_t *index)
{
	const size_t	start = *index;
	const size_t	len = ft_strlen(str);
	char			quote;

	while (*index < len && !((is_space_or_tab(str[*index]) || is_metachar(str[*index])) && !is_escaped(str, *index)))
	{
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
	}
	return (*index - start);
}

static char		*cut_out_one_word(const char *str, size_t *index)
{
	const size_t	start = *index;
	const size_t	len = get_ret_s_len(str, index);

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

char		**split_command_line_with_quotes(char const *str)
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

void	trim_quotes_if_not_env(char **words)
{
	size_t	index;
	char	*tmp;

	index = 0;
	while (words[index])
	{
		if (str_is_quoted(words[index]) && !str_has_env(words[index]))
		{
			tmp = words[index];
			words[index] = ft_strndup((&tmp[1]), ft_strlen(tmp) - 2);
			free(tmp);
		}
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

// クオーテーションでは区切らない

