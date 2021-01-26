#include "minishell.h"

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
