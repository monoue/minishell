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

char		**split_command_line(char const *str)
{
	char	**words;

	words = split_command_line_with_quotes(str);
	if (!words)
		return (NULL);
	trim_quotes_if_not_env(words);
	return (words);
}
