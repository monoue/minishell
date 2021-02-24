/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/24 14:35:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_flag_dont;

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
	if (argv[0] == '\'')
		return (do_single_quotation(argv, envp));
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
	if (!(tmp = malloc(sizeof(*tmp) * (MAX_INPUT * MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	while (line[i])
	{
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

char	*exec_dollar(char **tmp, t_list *envp)
{
	int		j;
	char	*value;
	char	*str;
	char	*final;

	j = 0;
	str = NULL;
	value = NULL;
	while (tmp[j])
	{
		g_flag = false;
		g_flag_dont = false;
		if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"')
			str = go_parse_dq(tmp[j], envp, 0);
		else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
			str = replace_dollar_value(tmp[j], envp);
		else
			str = ft_strdup(tmp[j]);
		final = return_final(str, tmp, j);
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

	g_flag = false;
	g_flag_escape_db = false;
	g_flag_dont = false;
	g_global = true;
	final = NULL;
	tmp = do_parse(argv);
	value = exec_dollar(tmp, envp);
	final = ft_strdup(value);
	SAFE_FREE(value);
	ft_free_split(tmp);
	if (ft_strcmp(final, "") == 0 && !g_flag_escape_db)
	{
		free(final);
		return (NULL);
	}
	return (final);
}
