/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:01:11 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 14:03:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space_dq(char *value)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(value);
	if (!(tmp = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (value[i] == ' ' || value[i] == '\t')
		i++;
	while (i < j)
	{
		while (value[i] != ' ' && value[i] && value[i] != '\t')
		{
			tmp = ft_strnjoin_free(tmp, &value[i], 1);
			i++;
		}
		if (value[i] != '\0' && value[i + 1] != '\0')
			tmp = ft_strnjoin_free(tmp, " ", 1);
		i++;
	}
	return (tmp);
}

char	*skip_space_sq(char *value)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(value);
	if (!(tmp = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (i < j)
	{
		while (value[i] != ' ' && value[i] && value[i] != '\t')
		{
			tmp = ft_strnjoin_free(tmp, &value[i], 1);
			i++;
		}
		if (value[i] != '\0')
			tmp = ft_strnjoin_free(tmp, " ", 1);
		i++;
	}
	return (tmp);
}

bool	check_dollar_question(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] == '?')
			return (true);
		i++;
	}
	return (false);
}
