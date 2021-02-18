/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/18 18:42:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable(char *variable)
{
	int		count;
	char	*value;
	char	*tmp_var;

	if (!variable)
		return (NULL);
	tmp_var = NULL;
	value = NULL;
	count = ft_strrchr_int(variable, '=');
	tmp_var = ft_substr(variable, count + 1, ft_strlen(variable) - count);
	if (g_flag == 0)
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

char	*replace_dollar_value(char *argv, t_list *envp, int g_flag)
{
	char	*value;

	value = NULL;
	g_space = false;
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
	int		tmp_num;

	j = 0;
	i = 0;
	tmp_num = ft_strlen(line);
	tmp = malloc(sizeof(*tmp) * (tmp_num));
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

	j = 0;
	str = NULL;
	value = NULL;
	while (tmp[j])
	{
		if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"')
			str = go_parse_dq(tmp[j], envp, 0);
		else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
			str = replace_dollar_value(tmp[j], envp, 0);
		else
			str = remove_quotes(ft_strdup(tmp[j]));
		value = ft_strjoin_free(value, str);
		SAFE_FREE(str);
		str = NULL;
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
	final = NULL;
	tmp = do_parse(argv);
	value = exec_dollar(tmp, envp);
	final = remove_escape(value);
	SAFE_FREE(value);
	ft_free_split(tmp);
	return (final);
}
