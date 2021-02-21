/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:48:24 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/20 15:38:47 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_escape(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	while (line[*i] != '\0' && !ft_isascii1(line[*i]) && !ft_isalnum(line[*i]))
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
