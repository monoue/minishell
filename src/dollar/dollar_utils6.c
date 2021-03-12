/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:01:11 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 13:52:21 by monoue           ###   ########.fr       */
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
	while (value[i] == ' ')
		i++;
	while (i < j)
	{
		while (value[i] != ' ' && value[i])
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
		while (value[i] != ' ' && value[i])
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

// char	*return_value(char **tmp, int i, char *arg, char *str)
// {

// 	if (((tmp[i][0] != '\"' && tmp[i][0] != '\'')
// 		|| ((tmp[i][0] == '\"' && tmp[i][1] == '\"')
// 		|| (tmp[i][0] == '\'' && tmp[i][1] == '\''))))
// 	{
// 		str = remove_quotes(tmp[i]);
// 		arg = remove_escape(str, 0);
// 	}
// 	else if (tmp[i][0] != '\'')
// 	{
// 		str = remove_escape_dq(tmp[i]);
// 		arg = remove_quotes(str);
// 	}
// 	else
// 	{
// 		str = remove_quotes(tmp[i]);
// 		arg = ft_strdup(str);
// 	}
// 	return (arg);
// }
