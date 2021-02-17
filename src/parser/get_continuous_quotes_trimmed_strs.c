#include "minishell.h"

static bool	is_continuous_quotes(char *str, size_t index)
{
	return ((ft_strnequal(&str[index], "\'\'", 2)
				|| ft_strnequal(&str[index], "\"\"", 2))
				&& !is_escaped(str, index));
}

static char	*get_continuous_quotes_trimmed_str(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;
	
	ret_s = ft_strdup("");
	if (!ret_s)
		return (NULL);
	index = 0;
	while (index < len)
	{
		while (index < len && is_continuous_quotes(str, index))
			index += 2;
		start = index;	
		while (index < len && !is_continuous_quotes(str, index))
			index++;
		ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
	}
	return (ret_s);
}

char		**get_continuous_quotes_trimmed_strs(char **src_strs)
{
	const size_t	strs_num = ft_count_strs((const char **)src_strs);
	size_t			index;
	char			**dst_strs;

	if (!src_strs)
		return (NULL);
	dst_strs = malloc((strs_num + 1) * sizeof(char *));
	if (!dst_strs)
		return (NULL);
	index = 0;
	while (index < strs_num)
	{
		dst_strs[index] = get_continuous_quotes_trimmed_str(src_strs[index]);
		index++;
	}
	dst_strs[index] = NULL;
	return (dst_strs);
}
