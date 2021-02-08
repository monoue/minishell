#include "../minishell.h"

bool	is_escaped(const char *str, size_t index)
{
	if (index == 0)
		return (false);
	return (str[index - 1] == '\\');
}
