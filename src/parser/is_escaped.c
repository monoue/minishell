#include "minishell.h"

bool	is_escaped(const char *str, size_t index)
{
	size_t	b_slash_num;
	int		i;
	
	if (index == 0)
		return (false);
	i = index - 1;
	b_slash_num = 0;
	while (i >= 0 && str[i] == '\\')
	{
		b_slash_num++;
		i--;
	}
	return (b_slash_num % 2);
}
