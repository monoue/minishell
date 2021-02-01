#include "minishell.h"

t_type	get_redirection_type(char *element)
{
	const t_redirection_combination redirection_sets[] = {
		{">", TYPE_OUTPUT},
		{">>", TYPE_APPEND},
		{"<", TYPE_INPUT},
		{NULL, TYPES_NUM}
	};
	size_t					index;

	index = 0;
	while (index < TYPES_NUM)
	{
		if (ft_strequal(element, redirection_sets[index].symbol))
			return (redirection_sets[index].type);
		index++;
	}
	return (ERROR);
}