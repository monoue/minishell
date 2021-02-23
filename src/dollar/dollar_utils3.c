/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:21:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/23 21:26:33 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *arg, t_list *envp)
{
	char	*variable;
	t_list	*tmp_list;

	if (!(variable = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	tmp_list = envp;
	while (tmp_list && tmp_list->next)
	{
		if (ft_strncmp((char*)tmp_list->content, arg, ft_strlen(arg)) == 0)
			variable = ft_strnjoin_free(variable,
			(char*)tmp_list->content, ft_strlen((char*)tmp_list->content));
		tmp_list = tmp_list->next;
	}
	if (ft_strcmp(variable, "") == 0)
		return (NULL);
	return (variable);
}

char	*take_dollar(char *line, int *i)
{
	char	*tmp;

	tmp = ft_strnjoin_free(tmp, &line[*i], 1);
	(*i)++;
	if (line[*i] == '$')
	{
		free(tmp);
		tmp = ft_strdup("(process ID)");
		(*i)++;
		return (tmp);
	}
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
		&& line[*i] != '$' && line[*i] != '\0'
		&& line[*i] != '\\')
	{
		tmp = ft_strnjoin_free(tmp, &line[*i], 1);
		(*i)++;
	}
	return (tmp);
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
