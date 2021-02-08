#include "../minishell.h"

// static void	skip_word(char const *str, size_t *index)
// {
// 	char			quote;
// 	const size_t	len = ft_strlen(str);

// 	// while (index < len && !is_space_or_tab(str[*index]) && !is_metachar(str[*index]) && !is_escaped(str, *index))
// 	while (*index < len && !((is_space_or_tab(str[*index]) || is_metachar(str[*index])) && !is_escaped(str, *index)))
// 	{
// 		// if (get_quote_type(str[*index]))
// 		if (is_specific_char_not_escaped(str, *index, is_quote_char))
// 		{
// 			quote = str[*index];
// 			(*index)++;
// 			// while (str[*index] != quote)
// 			while (!(str[*index] == quote && !is_escaped(str, *index)))
// 				(*index)++;
// 			(*index)++;
// 		}
// 		else
// 		{
// 			// while (str[*index] != '\0' && !get_quote_type(str[*index]) && !is_metachar(str[*index]) && !is_space_or_tab(str[*index]))
// 			while (*index < len && !((get_quote_type(str[*index]) || is_metachar(str[*index]) || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
// 				(*index)++;
// 		}
// 	}
// }

static void	skip_word(char const *str, size_t *index)
{
	char			quote;
	const size_t	len = ft_strlen(str);

	// while (index < len && !is_space_or_tab(str[*index]) && !is_metachar(str[*index]) && !is_escaped(str, *index))
	// while (*index < len && !((is_space_or_tab(str[*index]) || is_metachar(str[*index])) && !is_escaped(str, *index)))
	// {
		// if (get_quote_type(str[*index]))
		if (is_specific_char_not_escaped(str, *index, is_quote_char))
		{
			quote = str[*index];
			(*index)++;
			// while (str[*index] != quote)
			while (!(str[*index] == quote && !is_escaped(str, *index)))
				(*index)++;
			(*index)++;
		}
		else
		{
			// while (str[*index] != '\0' && !get_quote_type(str[*index]) && !is_metachar(str[*index]) && !is_space_or_tab(str[*index]))
			while (*index < len && !((get_quote_type(str[*index]) || is_metachar(str[*index]) || is_space_or_tab(str[*index])) && !is_escaped(str, *index)))
				(*index)++;
		}
	// }
}

size_t		count_command_line_words(char const *str)
{
	size_t			index;
	size_t			words_num;
	const size_t	len = ft_strlen(str);

	index = 0;
	// while (str[index] != '\0' && is_space_or_tab(str[index]))
	while (index < len && is_specific_char_not_escaped(str, index, is_space_or_tab))
		index++;
	words_num = 0;
	while (index < len)
	{
		if (ft_strnequal(&str[index], ">>", 2) && !is_escaped(str, index))
			index += 2;
		// else if (is_metachar(str[index]))
		else if (is_specific_char_not_escaped(str, index, is_metachar))
			index++;
		else // 文字、もしくは quote 始まり
			skip_word(str, &index);
		// while (str[index] != '\0' && is_space_or_tab(str[index])) // 空白スキップ
		while (index < len && is_specific_char_not_escaped(str, index, is_space_or_tab)) // 空白スキップ
			index++;
		words_num++;
	}
	return (words_num);
}
