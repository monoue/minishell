#include "minishell.h"

bool	is_quoted_wrongly(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	char			quote;

	index = 0;
	while (index < len)
	{
		if (str[index] == '\'' || str[index] == '\"')
		{
			quote = str[index];
			index++;
			while (index < len && str[index] != quote)
				index++;
			if (index == len)
				return (true);
		}
		index++;
	}
	return (false);
}
