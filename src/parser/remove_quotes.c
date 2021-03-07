/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:57:58 by monoue            #+#    #+#             */
/*   Updated: 2021/03/05 18:25:10 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*remove_escape(const char *str, size_t index)
{
	const size_t	len = ft_strlen(str);
	size_t			start;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
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

char	*exec_escape_dq(const char *str, int index, int len, int start)
{
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (index < len)
	{
		start = index;
		if (check_is_escape(str, index))
		{
			index += 2;
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], 1);
		}
		else if (str[index] == '\\' && str[index + 1] == '\'')
		{
			index += 2;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
		else
		{
			check_escape(str, &index, &len);
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}

char	*remove_escape_dq(const char *str)
{
	return (exec_escape_dq(str, 0, ft_strlen(str), 0));
}

char		*skip_plus(char *str)
{
	const size_t	len = ft_strlen(str);
	size_t			start;
	size_t			index;
	char			*ret_s;

	if (!(ret_s = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (index < len)
	{
		start = index;
		if (str[index] == '+')
		{
			index += 2;
			ret_s = ft_strnjoin_free(ret_s, &str[start + 1], 1);
		}
		else
		{
			while (index < len && str[index] != '+')
				index++;
			ret_s = ft_strnjoin_free(ret_s, &str[start], index - start);
		}
	}
	return (ret_s);
}
