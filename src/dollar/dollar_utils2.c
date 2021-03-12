/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:59:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/08 16:08:57 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space_dollar(char *value)
{
	char	*tmp;

	if (g_flag_escape_db == 1)
		tmp = skip_space_dq(value);
	else
		tmp = skip_space_sq(value);
	return (tmp);
}

char	*do_single_quotation(char *argv, t_list *envp, int j)
{
	char	**tmp;
	char	*str;
	char	*value;
	char	*final;

	g_flag = true;
	g_flag_escape_db = true;
	value = NULL;
	tmp = do_parse3(argv);
	while (tmp[j])
	{
		g_flag_dont = false;
		if (has_dollar_variable(tmp[j]))
			str = replace_dollar_value(tmp[j], envp);
		else
			str = ft_strdup(tmp[j]);
		final = return_final(str, tmp, j);
		value = ft_strnjoin_free(value, final, ft_strlen(final));
		SAFE_FREE(str);
		SAFE_FREE(final);
		j++;
	}
	ft_free_split(tmp);
	return (value);
}

int		single_quotation_or_not(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*take_dollar_dq(char *line, int *i)
{
	char	*tmp;

	if (!(tmp = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	if (ft_isdigit(line[*i]))
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
		return (tmp);
	}
	while (line[*i] != '\'' && line[*i] != '\"'
			&& line[*i] != '\0' && line[*i] != '$' && line[*i] != '/'
			&& line[*i] != '\\' && line[*i] != '='
			&& ft_isalnum(line[*i]))
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
}

char	**do_parse2(char *line)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(tmp = malloc(sizeof(*tmp) * (MAX_INPUT * MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	while (line[i])
	{
		if (line[i] == '\"')
			i++;
		if (line[i] == '$')
			tmp[j++] = take_dollar(line, &i);
		if (line[i] == '\'')
			tmp[j++] = take_single_quote(line, &i);
		if (ft_isascii1(line[i]) || line[i] == '/')
			tmp[j++] = take_ascii(line, &i);
		if (line[i] == '\\')
			tmp[j++] = take_escape(line, &i);
	}
	tmp[j] = NULL;
	return (tmp);
}
