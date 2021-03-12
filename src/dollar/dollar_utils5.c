/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:43:56 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 13:54:26 by monoue           ###   ########.fr       */
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

// char	*remove_all(char *argv)
// {
// 	char	*str;
// 	char	**tmp;
// 	char	*arg;
// 	char	*final;
// 	int		i;

// 	i = 0;
// 	final = ft_strdup("");
// 	tmp = do_parse(argv);
// 	while (tmp[i])
// 	{
// 		if (tmp[i][0] == '\\' && (tmp[i][1] == '\"' || tmp[i][1] == '\''))
// 			g_escape = 1;
// 		str = return_value(tmp, i, arg, str);
// 		final = ft_strjoin_free_both(final, str);
// 		i++;
// 		SAFE_FREE(arg);
// 	}
// 	tmp[i] = NULL;
// 	ft_free_split(tmp);
// 	return (final);
// }

static bool	quote_check(char *str)
{
	return (((str[0] != '\"' && str[0] != '\'')
        || ((str[0] == '\"' && str[1] == '\"')
        || (str[0] == '\'' && str[1] == '\''))));
}

char    *remove_all(char *argv)
{
    char    *str;
    char    **tmp;
    char    *arg;
    char    *final;
    int        index;

    index = 0;
    final = ft_strdup("");
    tmp = do_parse(argv);
    while (tmp[index])
    {
        if (tmp[index][0] == '\\' && (tmp[index][1] == '\"' || tmp[index][1] == '\''))
            g_escape = 1;
        if (quote_check(tmp[index]))
        {
            str = remove_quotes(tmp[index]);
            arg = remove_escape(str, 0);
        }
        else if (tmp[index][0] != '\'')
        {
            str = remove_escape_dq(tmp[index]);
            arg = remove_quotes(str);
            SAFE_FREE(str);
        }
        else
        {
            str = remove_quotes(tmp[index]);
            arg = ft_strdup(str);
        }
        final = ft_strjoin_free_both(final, arg);
        index++;
    }
    tmp[index] = NULL;
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
