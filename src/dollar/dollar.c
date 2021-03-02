/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/01 16:42:50 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable(char *variable)
{
	int		count;
	char	*value;
	char	*tmp_var;

	tmp_var = NULL;
	value = NULL;
	if (!variable)
		return (ft_strdup(""));
	count = count_variable(variable);
	tmp_var = ft_substr(variable, count + 1, ft_strlen(variable) - count);
	if (g_flag == 0)
	{
		value = skip_space_dollar(tmp_var);
		g_space = 1;
	}
	else
		value = ft_strdup(tmp_var);
	SAFE_FREE(tmp_var);
	SAFE_FREE(variable);
	return (value);
}

char	*replace_dollar_value(char *argv, t_list *envp)
{
	char	*value;

	value = NULL;
	g_space = 0;
	g_flag_dont = 1;
	g_into_dollar = 1;
	if (argv[0] == '\'')
		return (do_single_quotation(argv, envp, 0));
	value = find_variable(find_key_1(argv, envp));
	return (value);
}

char	**do_parse(char *line)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(tmp = malloc(sizeof(*tmp) * (MAX_INPUT * MAX_INPUT * MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			i++;
		if (line[i] == '$')
			tmp[j++] = take_dollar(line, &i);
		if (line[i] == '\'')
			tmp[j++] = take_single_quote(line, &i);
		if (ft_isascii1(line[i]) || line[i] == '/')
			tmp[j++] = take_ascii(line, &i);
		if (line[i] == '\\')
			tmp[j++] = take_escape(line, &i);
		if (line[i] == '\"')
			tmp[j++] = take_double_quote(line, &i);
	}
	return (tmp);
}

char	*exec_dollar(char **tmp, t_list *envp, int j)
{
	char	*value;
	char	*str;
	char	*final;

	value = NULL;
	while (tmp[j])
	{
		g_flag = 0;
		g_flag_dont = 0;
		if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"'
			&& (tmp[j][0] == '$' && tmp[j][1] != '?'))
			str = go_parse_dq(tmp[j], envp, 0);
		else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\''
				&& (tmp[j][0] == '$' && tmp[j][1] != '?'))
			str = replace_dollar_value(tmp[j], envp);
		else
			str = ft_strdup(tmp[j]);
		final = remove_final(str, tmp, j);
		value = ft_strjoin_free(value, final);
		SAFE_FREE(str);
		SAFE_FREE(final);
		j++;
	}
	return (value);
}

char	*dollar(char *argv, t_list *envp)
{
	char	**tmp;
	char	*final;
	char	*value;

	g_flag = 0;
	g_flag_escape_db = 0;
	g_flag_dont = 0;
	g_global = 1;
	final = NULL;
	tmp = do_parse(argv);
	value = exec_dollar(tmp, envp, 0);
	final = ft_strdup(value);
	SAFE_FREE(value);
	ft_free_split(tmp);
	if (ft_strcmp(final, "") == 0 && g_flag_escape_db == 0)
	{
		SAFE_FREE(final);
		return (NULL);
	}
	return (final);
}
