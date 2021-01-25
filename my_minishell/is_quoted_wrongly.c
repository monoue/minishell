#include "minishell.h"

bool	is_quoted_wrongly(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;

	index = 0;
	while (index < len)
	{
		if (str[index] == '\"')
		{
			while (index < len && str[index] != '\"')
				index++;
			if (index == len)
				return (true);
		}
		if (str[index] == '\'')
		{
			while (index < len && str[index] != '\'')
				index++;
			if (index == len)
				return (true);
		}
		index++;
	}
	return (false);
}
