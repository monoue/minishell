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

static void	trim_quotes_if_not_env(char **words)
{
	size_t	index;

	index = 0;
	while (words[index])
	{
		if (str_is_quoted(words[index]) && !str_has_env(words[index]))
			words[index] = ft_substr_free(words[index], 1,
												ft_strlen(words[index]) - 2);
		index++;
	}
}

// char		*turn_dollar_question_into_value(const char *str)
// {
// 	const size_t	len = ft_strlen(str);
// 	size_t			index;
// 	size_t			start;
// 	char			*ret_s;

// 	if (!(ret_s = ft_strdup("")))
// 		exit_err_msg(MALLOC_ERR);
// 	index = 0;
// 	while (index < len)
// 	{
// 		start = index;
// 		if (str[index] == '\'' && !is_escaped(str, index))
// 		{
// 			skip_quotes(str, &index);
// 			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], index - start - 2);
// 		}
// 		else if (ft_strnequal(&str[index], DOLLAR_Q, 2) && !is_escaped(str, index))
// 		{
// 			ret_s = ft_strjoin_free(ret_s, ft_itoa(g_last_exit_status));
// 			index += 2;
// 		}
// 		else
// 		{
// 			while (index < len && !((str[index] == '\'' || ft_strnequal(&str[index], DOLLAR_Q, 2)) && !is_escaped(str, index)))
// 				index++;
// 			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
// 		}
// 	}
// 	return (ret_s);
// }

void	skip_env(char const *str, size_t *index)
{
	char			quote;
	const size_t	len = ft_strlen(str);

	(*index)++;
	while (*index < len && !((str[*index] == '$' || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
		(*index)++;
}

char		*turn_dollar_question_into_value(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (str[index] == '\'' && !is_escaped(str, index))
		{
			skip_quotes(str, &index);
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], index - start - 2);
		}
		else if (str[index] == '$' && !is_escaped(str, index))
		{
			skip_env(str, &index);
			if (ft_strnequal(&str[start]))
			ret_s = ft_strjoin_free(ret_s, ft_itoa(g_last_exit_status));
			index += 2;
		}
		else
		{
			while (index < len && !((str[index] == '\'' || str[index] == '$') && !is_escaped(str, index)))
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}

char		**split_command_line(char const *str)
{
	char	**words;
	char	*tmp;

	// TODO: search する関数も一応作ってあげるか...
	tmp = turn_dollar_question_into_value(str);
	words = split_command_line_with_quotes(tmp);
	if (!words)
		return (NULL);
	trim_quotes_if_not_env(words);
	return (words);
}
