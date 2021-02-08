#include "../minishell.h"

bool	is_specific_char_not_escaped(const char *str, size_t index, bool(*func)(char))
{
	if (!func(str[index]))
		return (false);
	return (!is_escaped(str, index));
}
