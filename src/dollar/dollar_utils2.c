/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:59:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/23 13:07:16 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space_dollar(char *value)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!(tmp = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (value[i])
	{
		if (value[i] != ' ')
			tmp = ft_strnjoin_free(tmp, &value[i], 1);
		else if (value[i] == ' ' && value[i + 1] != ' ')
			tmp = ft_strnjoin_free(tmp, &value[i], 1);
		i++;
	}
	return (tmp);
}

char	*do_single_quotation(char *argv, t_list *envp)
{
	char	*buf;
	int		i;
	char	*str;
	char	*value;

	i = 0;
	str = NULL;
	value = NULL;
	buf = NULL;
	while (argv[i])
	{
		if (argv[i] == '\'')
		{
			i++;
			buf = into_single_quotes(argv, &i);
			g_flag = 1;
		}
		i++;
	}
	str = replace_dollar_value(buf, envp);
	value = replace_word(argv, buf, str, 0);
	// SAFE_FREE(str);
	// SAFE_FREE(buf);
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
	if (!(tmp = malloc(sizeof(*tmp) * (MAX_INPUT))))
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
	return (tmp);
}
