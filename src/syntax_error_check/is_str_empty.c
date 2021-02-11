#include "minishell.h"

bool	str_is_of_spaces(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	
	index = 0;
	while (str[index] == ' ')
		index++;
	return (index == len);
}
