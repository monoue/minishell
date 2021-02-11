#include "minishell.h"

static void	skip_spaces(const char *str, size_t *index)
{
	const size_t	len = ft_strlen(str);

	while (*index < len && is_specific_char_not_escaped(str, *index,
															is_space_or_tab))
		(*index)++;
}

size_t		count_command_line_words(char const *str)
{
	size_t			index;
	size_t			words_num;
	const size_t	len = ft_strlen(str);

	index = 0;
	skip_spaces(str, &index);
	words_num = 0;
	while (index < len)
	{
		if (ft_strnequal(&str[index], ">>", 2) && !is_escaped(str, index))
			index += 2;
		else if (is_specific_char_not_escaped(str, index, is_metachar))
			index++;
		else // 文字、もしくは quote 始まり
			skip_chunk(str, &index);
		skip_spaces(str, &index);
		words_num++;
	}
	return (words_num);
}
