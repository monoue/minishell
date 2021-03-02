/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 09:11:40 by monoue           ###   ########.fr       */
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
	char	**parsed_arg;
	size_t	index;
	size_t	strs_i;

	if (!(parsed_arg = malloc(sizeof(char *) * (MAX_INPUT * MAX_INPUT * MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	index = 0;
	strs_i = 0;
	while (line[index])
	{
		if (is_dollar(line[index]) && is_quote_char(line[index + 1]))
			index++;
		if (is_dollar(line[index]))
			parsed_arg[strs_i++] = take_dollar(line, &index);
		if (line[index] == '\'')
			parsed_arg[strs_i++] = take_single_quote(line, &index);
		if (ft_isascii1(line[index]) || line[index] == '/')
			parsed_arg[strs_i++] = take_ascii(line, &index);
		if (line[index] == '\\')
			parsed_arg[strs_i++] = take_escape(line, &index);
		if (line[index] == '\"')
			parsed_arg[strs_i++] = take_double_quote(line, &index);
	}
	return (parsed_arg);
}

char	*get_pre_final(char *str, t_list *envp)
{
	if (has_dollar_variable(str) && head_char_equal(str, '\"'))
		return (go_parse_dq(str, envp, 0));
	if (has_dollar_variable(str) && head_char_equal(str, '$') && str[1] != '?')
		return (replace_dollar_value(str, envp));
	return (ft_strdup(str));
}

char	*exec_dollar(char **parsed_arg, t_list *envp, size_t index)
{
	char			*value;
	char			*pre_final;
	char			*final;
	const size_t	strs_num = ft_count_strs((const char **) parsed_arg);

	value = NULL;
	while (index < strs_num)
	{
		g_flag = false;
		g_flag_dont = false;
		pre_final = get_pre_final(parsed_arg[index], envp);
		final = remove_final(pre_final,
									head_char_equal(parsed_arg[index], '\''));
		SAFE_FREE(pre_final);
		value = ft_strjoin_free_both(value, final);
		index++;
	}
	return (value);
}

char	*dollar(char *arg, t_list *envp)
{
	char	**parsed_arg;
	char	*value;

	g_flag = false;
	g_flag_escape_db = false;
	g_flag_dont = false;
	g_global = true;
	parsed_arg = do_parse(arg);
	value = exec_dollar(parsed_arg, envp, 0);
	ft_free_split(parsed_arg);
	if (!value)
		return (NULL);
	if (ft_strlen(value) == 0 && !g_flag_escape_db)
	{
		SAFE_FREE(value);
		return (NULL);
	}
	return (value);
}
