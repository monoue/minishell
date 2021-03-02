/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:48:24 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 18:37:04 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_escape(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	return (tmp);
}

char	**do_parse3(char *line)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(tmp = malloc(sizeof(*tmp) * (MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	while (line[i])
	{
		if (line[i] == '\'')
		{
			tmp[j++] = ft_strdup("\'");
			i++;
		}
		if (line[i] == '$')
			tmp[j++] = take_dollar(line, &i);
		if (ft_isascii1(line[i]) || line[i] == '/')
			tmp[j++] = take_ascii(line, &i);
		if (line[i] == '\\')
			tmp[j++] = take_escape(line, &i);
	}
	return (tmp);
}

int		count_variable(char *variable)
{
	char	*tmp;
	int		count;

	tmp = variable;
	count = 0;
	while (*tmp && *tmp != '=')
	{
		count++;
		tmp++;
	}
	return (count);
}

char	*return_final(char *str, char **tmp, int j)
{
	char	*quote;
	char	*final;
	int		a;

	a = 0;
	if (tmp[j][0] == '\'')
		a = 1;
	if (g_flag_dont == 0 && g_flag == 0)
		final = remove_quotes(str);
	else
		final = strdup(str);
	if (tmp[j][0] == '\\' && (tmp[j][1] == '\"' || tmp[j][1] == '\''))
		g_escape = 1;
	if (g_flag_dont == 0 && g_flag_escape_db == 0
			&& a != 1)
		quote = remove_escape(final, 0);
	else if (g_flag_dont == 0 && a != 1)
		quote = remove_escape_dq(final);
	else
		quote = ft_strdup(final);
	SAFE_FREE(final);
	return (quote);
}

char	*remove_final(char *str, char **tmp, int j)
{
	char	*final;
	char	*tmp_argv;

	if (tmp[j][0] != '\'')
		tmp_argv = turn_dollar_question_into_value(str);
	else
		tmp_argv = ft_strdup(str);
	if (g_flag == 0)
		final = return_final(tmp_argv, tmp, j);
	else
		final = ft_strdup(tmp_argv);
	SAFE_FREE(tmp_argv);
	return (final);
}
