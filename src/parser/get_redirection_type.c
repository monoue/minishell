#include "minishell.h"

int	get_redirection_type(char *element)
{
	const t_redirection_combination combs[] = {
		{">", TYPE_OUTPUT},
		{">>", TYPE_APPEND},
		{"<", TYPE_INPUT},
	};
	t_redirection_combination		comb;
	size_t							index;

	index = 0;
	while (index < TYPES_NUM)
	{
		comb = combs[index];
		if (ft_strequal(element, comb.symbol))
			return (comb.type);
		index++;
	}
	return (ERROR);
}
