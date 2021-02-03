#include "../minishell.h"

static void	skip_word(char const *str, size_t *index)
{
	char	quote;

	while (str[*index] != '\0' && !is_space_or_tab(str[*index]) && !is_redirection_char(str[*index]))
	{
		if (is_quote(str[*index]))
		{
			quote = str[*index];
			(*index)++;
			while (str[*index] != quote)
				(*index)++;
			(*index)++;
		}
		else
		{
			while (str[*index] != '\0' && !is_quote(str[*index]) && !is_redirection_char(str[*index]) && !is_space_or_tab(str[*index]))
				(*index)++;
		}
	}
}

size_t		count_command_argv(char const *str)
{
	size_t	index;
	size_t	words_num;

	index = 0;
	while (str[index] != '\0' && is_space_or_tab(str[index]))
		index++;
	words_num = 0;
	while (str[index] != '\0')
	{
		if (ft_strncmp(&str[index], ">>", 2) == 0)
			index += 2;
		else if (is_redirection_char(str[index]))
			index++;
		else // 文字、もしくは quote 始まり
			skip_word(str, &index);
		while (str[index] != '\0' && is_space_or_tab(str[index])) // 空白スキップ
			index++;
		words_num++;
	}
	return (words_num);
}
