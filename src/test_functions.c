
#include "minishell.h"

void	print_strs(char **strs)
{
	size_t	index = 0;
	while (strs[index])
	{
		DS(strs[index])	;
		index++;
	}
}