/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 19:39:39 by sperrin          ###   ########.fr       */
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
	if (!g_flag)
	{
		value = skip_space_dollar(tmp_var);
		g_space = true;
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
	g_space = false;
	g_flag_dont = true;
	g_into_dollar = true;
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
	char	*pre_final;
	char	*final;

	value = NULL;
	while (tmp[j])
	{
		g_flag = false;
		g_flag_dont = false;
		if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"')
			pre_final = go_parse_dq(tmp[j], envp, 0);
		else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\''
				&& (tmp[j][0] == '$' && tmp[j][1] != '?'))
			pre_final = replace_dollar_value(tmp[j], envp);
		else
			pre_final = ft_strdup(tmp[j]);
		final = remove_final(pre_final, tmp, j);
		value = ft_strjoin_free(value, final);
		SAFE_FREE(pre_final);
		SAFE_FREE(final);
		j++;
	}
	return (value);
}

char	*dollar(char *argv, t_list *envp)
{
	char	**parsed_arg;
	char	*final;
	char	*value;

	g_flag = false;
	g_flag_escape_db = false;
	g_flag_dont = false;
	g_global = true;
	final = NULL;
	parsed_arg = do_parse(argv);
	value = exec_dollar(parsed_arg, envp, 0);
	ft_free_split(parsed_arg);
	final = ft_strdup_free(value);
	if (ft_strequal(final, "") && !g_flag_escape_db)
	{
		SAFE_FREE(final);
		return (NULL);
	}
	return (final);
}
