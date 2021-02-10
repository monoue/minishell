#include "../minishell.h"

void	skip_word(const char *str, size_t *index)
{
	const size_t len = ft_strlen(str);

	while (*index < len && !((is_quote_char(str[*index])
								|| is_metachar(str[*index])
								|| is_space_or_tab(str[*index]))
								&& !is_escaped(str, *index)))
		(*index)++;
}
