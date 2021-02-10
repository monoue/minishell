#include "../minishell.h"

void	skip_chunk(char const *str, size_t *index)
{
	const size_t	len = ft_strlen(str);

	while (*index < len && !((is_space_or_tab(str[*index])
								|| is_metachar(str[*index]))
								&& !is_escaped(str, *index)))
	{
		if (is_specific_char_not_escaped(str, *index, is_quote_char))
			skip_quotes(str, index);
		else
			skip_word(str, index);
	}
}
