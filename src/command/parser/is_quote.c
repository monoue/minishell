#include "../../minishell.h"

bool	is_quote_char(char c)
{
	return (c == '\'' || c == '\"');
}
