/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:44:49 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 06:37:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_both_ends_quotes(char *str)
{
	const size_t	len = ft_strlen(str);
	char			*ret_s;

	if (is_specific_char_not_escaped(str, len - 1, is_quote_char) && str[0] == str[len - 1])
		ret_s = ft_strndup(&str[1], ft_strlen(str) - 2);
	else
		ret_s = ft_strdup(str);
	SAFE_FREE(str);
	return (ret_s);
}

char	*remove_quotes(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (is_specific_char_not_escaped(str, index, is_quote_char))
		{
			skip_quotes(str, &index);
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], index - start - 2);
		}
		else
		{
			while (index < len && !is_specific_char_not_escaped(str, index,
																is_quote_char))
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}

char	*remove_escape(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;

	if (g_flag_escape_db == 1)
		return (ret_s = ft_strdup(str));
	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (str[index] == '\\')
		{
			index += 2;
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], 1);
		}
		else
		{
			if (str[index] == '\\')
				index++;
			while (index < len && str[index] != '\\')
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}

char	*remove_escape_dq(const char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			index;
	size_t			start;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (str[index] == '\\' && str[index + 1] != '\'' 
		&& (str[index + 1 ] == '\"' || str[index + 1] == '$' || str[index + 1] == '\\') )
		{
			index += 2;
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], 1);
		}
		else if (str[index] == '\\' && str[index + 1] == '\'')
		{
			index++; 
			index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
		else
		{
			if (str[index] == '\\')
				index++;
			while (index < len && str[index] != '\\')
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}

