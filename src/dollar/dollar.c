/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/17 13:05:20 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		space;
int		flag;
int		flag_single_in_dq = 0;

char	*find_key_1(char *argv, t_list *envp)
{
	t_list	*tmp_list;
	char	*variable;
	char	*arg;

	arg = ft_strjoin(&argv[1], "=");
	tmp_list = envp;
	variable = NULL;
	while (tmp_list && tmp_list->next)
	{
		if (ft_strncmp((char*)tmp_list->content, arg, ft_strlen(arg)) == 0)
			variable = ft_strdup((char*)tmp_list->content);
		tmp_list = tmp_list->next;
	}
	free(arg);
	return (variable);
}

char	*find_variable(char *variable)
{
	int		count;
	char	*value;
	char	*tmp_var;

	tmp_var = NULL;
	value = NULL;
	if (!variable)
		return (ft_strdup(""));
	count = ft_strrchr_int(variable, '=');
	tmp_var = ft_substr(variable, count + 1, ft_strlen(variable) - count);
	if (flag == 0)
	{
		value = skip_space_dollar(tmp_var);
		space = 1;
	}
	else
		value = ft_strdup(tmp_var);
	free(tmp_var);
	free(variable);
	return (value);
}

char	*replace_dollar_value(char *argv, t_list *envp, int flag)
{
	char	*value;

	value = NULL;
	space = 0;
	if (argv[0] == '\'' && flag_single_in_dq == 1)
	{
		return (do_single_quotation(argv, envp));
		flag = 1;
	}
	value = find_variable(find_key_1(argv, envp));
	if (ft_strcmp(value, "") == 0)
		return (NULL);
	return (value);
}

char	*take_double_quote(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	while (line[*i] != '\"')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	return (tmp);
}

char	*take_escape(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	while (line[*i] != '$' && line[*i] != '\0'
		&& !ft_isascii1(line[*i]))
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
}

char	*take_ascii(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (line[*i] == '/')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
		return (tmp);
	}
	while (line[*i] != '\"' && line[*i] != '\''
		&& line[*i] != '$' && line[*i] != '\0')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
}

char	*take_single_quote(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	while (line[*i] != '\'')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	return (tmp);
}


char	*take_dollar(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	if (line[*i] == '$')
	{
		free(tmp);
		tmp = ft_strdup("(process ID)");
		(*i)++;
		return (tmp);
	}
	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	while (line[*i] != '\'' && line[*i] != '\"'
			&& line[*i] != '\0' && line[*i] != '$' && line[*i] != '/'
			&& line[*i] != '\\' && line[*i] != '='
			&& !ft_isdigit(line[*i]))
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
}

char	**do_parse(char *line)
{
	char	**tmp;
	int		i;
	int		j;
	int		tmp_num;

	j = 0;
	i = 0;
	tmp_num = count_command_line_words(line);
	tmp = malloc(sizeof(*tmp) * (tmp_num + 10000));
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

char	*dollar(char *argv, t_list *envp, int j)
{
	char	**tmp;
	char	*str;
	int		tmp_num;
	char	*value;
	char	*final;

	j = 0;
	tmp_num = count_command_line_words(argv);
	tmp = malloc(sizeof(*tmp) * (tmp_num + 10000));
	str = NULL;
	value = NULL;
	final = NULL;
	tmp = do_parse(argv);
	j = 0;
	while (tmp[j])
	{
		if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"')
			str = go_parse_dq(tmp[j], envp);
		else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
			str = replace_dollar_value(tmp[j], envp, 0);
		else
			str = remove_quotes(ft_strdup(tmp[j]));
		value = ft_strnjoin_free(value, str, ft_strlen(str));
		free(str);
		str = NULL;
		j++;
	}
	ft_free_split(tmp);
	flag = 0;
	final = remove_escape(value);
	return (final);
}
