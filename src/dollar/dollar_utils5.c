/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 07:24:19 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_dollar_bis(char *line, int *i, char *tmp)
{
	if (line[*i] == '$')
	{
		SAFE_FREE(tmp);
		(*i)++;
		return (tmp = ft_strdup("(processID)"));
	}
	if (line[*i] == '?')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
		return (tmp);
	}
	return (tmp);
}

void	check_escape(const char *str, int *index, int *len)
{
	if (str[*index] == '\\')
		(*index)++;
	while (*index < *len && str[*index] != '\\')
		(*index)++;
}

bool	check_is_escape(const char *str, int index)
{
	if (str[index] == '\\' && str[index + 1] != '\''
		&& (str[index + 1] == '\"' || str[index + 1] == '$'
		|| str[index + 1] == '\\' || str[index + 1] == '`'))
		return (true);
	return (false);
}

char	*remove_all(char *argv)
{
	char	*str;
	char	**tmp;
	char	*arg;
	char	*final;
	int		i;

	i = 0;
	final = ft_strdup("");
	tmp = do_parse(argv);
	while (tmp[i])
	{
		if (tmp[i][0] == '\\' && (tmp[i][1] == '\"' || tmp[i][1] == '\''))
			g_escape = 1;
		str = return_value(tmp, i, arg, str);
		final = ft_strjoin_free(final, str);
		i++;
		SAFE_FREE(arg);
		SAFE_FREE(str);
	}
	tmp[i] = NULL;
	ft_free_split(tmp);
	return (final);
}

int		check_quote(int a, char *line)
{
	int	b;

	b = 0;
	while (line[a])
	{
		if (line[a] == '\'')
			b++;
		a++;
	}
	return (b);
}
