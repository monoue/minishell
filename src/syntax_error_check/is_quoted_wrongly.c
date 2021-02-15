#include "minishell.h"

bool	is_quoted_wrongly(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	char			quote;

	index = 0;
	while (index < len)
	{
		if (str[index] == '\\')
		{
			if (is_quote_char(str[index + 1]))
			{
				quote = str[index + 1];
				index += 2;
				while (index < len)
				{
					if (str[index] == '\\')
					{
						if (str[index + 1] == quote)
						{
							index += 2;
							break ;
						}
						index += 2;
					}
				}
			}
			else
				index += 2;
		}
		if (is_specific_char_not_escaped(str, index, is_quote_char))
		{
			quote = str[index];
			index++;
			while (index < len && !(str[index] == quote && !is_escaped(str, index)))
				index++;
			if (index == len)
				return (true);
		}
		index++;
	}
	return (false);
}
