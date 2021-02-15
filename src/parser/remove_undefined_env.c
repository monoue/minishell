#include "minishell.h"

void	skip_env(char const *str, size_t *index)
{
	const size_t	len = ft_strlen(str);

	(*index)++;
	while (*index < len && !((str[*index] == '$' || is_space_or_tab(str[*index]) || ft_strchr(SYMBOL_CHARS, str[*index])) && !is_escaped(str, *index)))
	// is_escaped 使う
		(*index)++;
	(*index)++;
}

char		*remove_undefined_env(const char *str, t_list *envp)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;
	char			*env;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (str[index] == '\'' && !is_escaped(str, index))
		{
			skip_quotes(str, &index);
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
		else if (str[index] == '$' && !is_escaped(str, index))
		{
			skip_env(str, &index);
			env = ft_strndup(&str[start], index - start);
			// if (replace_dollar_value(env, envp)[0] == '\0' || ft_strequal(env, DOLLAR_Q))
			if (replace_dollar_value(env, envp)[0] != '\0' || ft_strequal(env, DOLLAR_Q))
				ret_s = ft_strjoin_free(ret_s, env);
		}
		else
		{
			while (index < len && !((str[index] == '\'' || str[index] == '$') && !is_escaped(str, index)))
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}
