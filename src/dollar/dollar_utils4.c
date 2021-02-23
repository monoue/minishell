/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:48:24 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/23 13:07:43 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_escape(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	while (line[*i] != '\0' && !ft_isascii1(line[*i])
		&& !ft_isalnum(line[*i]) && line[*i] != '$')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
}

char	*into_single_quotes(char *argv, int *i)
{
	char	*tmp;

	if (!(tmp = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (argv[*i] != '\'')
	{
		tmp = ft_strnjoin_free(tmp, &argv[*i], 1);
		(*i)++;
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

	if (g_flag_dont == 0 && tmp[j][0] != '\''
		&& tmp[j][0] != '\"')
		quote = remove_escape(str);
	else if (g_flag_dont == 0 && tmp[j][0] == '\"')
		quote = remove_escape_dq(str);
	else
		quote = ft_strdup(str);
	if (g_flag == 0)
		final = remove_quotes(quote);
	else
		final = strdup(quote);
	// SAFE_FREE(quote);
	return (final);
}
