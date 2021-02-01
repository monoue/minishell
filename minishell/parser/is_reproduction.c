#include "../minishell.h"

bool	is_reproduction(char *word)
{
	const char	*reproductions[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	size_t		index;

	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(word, reproductions[index]))
			return (true);
		index++;
	}
	return (false);
}
