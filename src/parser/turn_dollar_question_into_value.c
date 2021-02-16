#include "minishell.h"

static void	turn_dollar_question_into_value_loop(const char *str, size_t *index,
													char **ret_s, size_t len)
{
	const size_t	start = *index;

	if (str[*index] == '\'' && !is_escaped(str, *index))
	{
		skip_quotes(str, index);
		*ret_s = ft_strnjoin_free(*ret_s, &str[start], *index - start);
	}
	else if (ft_strnequal(&str[*index], DOLLAR_Q, 2)
												&& !is_escaped(str, *index))
	{
		*ret_s = ft_strjoin_free(*ret_s, ft_itoa(g_last_exit_status));
		*index += 2;
	}
	else
	{
		while (*index < len && !((str[*index] == '\''
				|| ft_strnequal(&str[*index], DOLLAR_Q, 2))
				&& !is_escaped(str, *index)))
		{
			(*index)++;
		}
		*ret_s = ft_strnjoin_free(*ret_s, &str[start], *index - start);
	}
}

char	*turn_dollar_question_into_value(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
		turn_dollar_question_into_value_loop(str, &index, &ret_s, len);
	return (ret_s);
}
