/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 14:10:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	quote_check(char *str)
{
	return (((str[0] != '\"' && str[0] != '\'')
		|| ((str[0] == '\"' && str[1] == '\"')
		|| (str[0] == '\'' && str[1] == '\''))));
}

static char	*remove_all_sub(char *tmp)
{
	char	*str;
	char	*arg;

	if (quote_check(tmp))
	{
		str = remove_quotes(tmp);
		arg = remove_escape(str, 0);
	}
	else if (tmp[0] != '\'')
	{
		str = remove_escape_dq(tmp);
		arg = remove_quotes(str);
	}
	else
	{
		str = remove_quotes(tmp);
		arg = ft_strdup(str);
	}
	SAFE_FREE(str);
	return (arg);
}

char		*remove_all(char *argv)
{
	char	**tmp;
	char	*arg;
	char	*final;
	int		index;

	index = 0;
	final = ft_strdup("");
	tmp = do_parse(argv);
	while (tmp[index])
	{
		if (tmp[index][0] == '\\'
			&& (tmp[index][1] == '\"' || tmp[index][1] == '\''))
		{
			g_escape = true;
		}
		arg = remove_all_sub(tmp[index]);
		final = ft_strjoin_free_both(final, arg);
		index++;
	}
	tmp[index] = NULL;
	ft_free_split(tmp);
	return (final);
}
