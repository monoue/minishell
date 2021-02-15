
#include "minishell.h"

void	put_strs(char **strs)
{
	size_t	index = 0;
	while (strs[index])
	{
		DS(strs[index])	;
		index++;
	}
}