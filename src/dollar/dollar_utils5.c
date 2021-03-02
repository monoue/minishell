/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 20:03:08 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_dollar_bis(char *line, int *i, char *tmp)
{
	if (line[*i] == '$')
	{
		SAFE_FREE(tmp);
		(*i)++;
		return (tmp = ft_strdup("(process ID)"));
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
		|| str[index + 1] == '\\'))
		return (true);
	return (false);
}

char	*remove_all(char *argv)
{
	int		index;
	char	*tmp;
	char	*str;
	char	*arg;

	index = 0;
	tmp = NULL;
	str = ft_strdup(argv);
	tmp = remove_quotes(str);
	if (argv[0] == '\\' && (argv[1] == '\"' || argv[1] == '\''))
		g_escape = 1;
	if (((argv[0] != '\"' && argv[0] != '\'')
		|| ((argv[0] == '\"' && argv[1] == '\"')
		|| (argv[0] == '\'' && argv[1] == '\''))))
		arg = remove_escape(tmp, 0);
	else if (argv[0] != '\'')
		arg = remove_escape_dq(tmp);
	else
		arg = ft_strdup(tmp);
	SAFE_FREE(str);
	SAFE_FREE(tmp);
	return (arg);
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
