/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:21:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 09:13:12 by monoue           ###   ########.fr       */
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
	{
		SAFE_FREE(variable);
		return (NULL);
	}
	return (variable);
}

char	*take_dollar(char *line, size_t *index)
{
	char	*tmp;
	size_t	*num;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*index], 1);
	(*index)++;
	num = index;
	tmp = take_dollar_bis(line, index, tmp);
	if (num != index)
		return (tmp);
	if (ft_isdigit(line[*index]))
	{
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
		return (tmp);
	}
	while (line[*index] != '\'' && line[*index] != '\"' && line[*index] != '\0'
			&& line[*index] != '$' && line[*index] != '/' && line[*index] != '\\'
			&& line[*index] != '=' && (ft_isalnum(line[*index]) || line[*index] == '_'))
	{
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
	}
	return (tmp);
}

char	*take_single_quote(char *line, size_t *index)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*index], 1);
	(*index)++;
	while (line[*index] != '\'')
	{
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
	}
	tmp = ft_strnjoin_free(tmp, &line[*index], 1);
	(*index)++;
	return (tmp);
}

char	*take_ascii(char *line, size_t *index)
{
	char	*tmp;

	tmp = NULL;
	if (line[*index] == '/')
	{
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
		return (tmp);
	}
	while (line[*index] != '\"' && line[*index] != '\''
		&& line[*index] != '$' && line[*index] != '\0'
		&& line[*index] != '\\')
	{
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
	}
	return (tmp);
}

char	*take_double_quote(char *line, size_t *index)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnjoin_free(tmp, &line[*index], 1);
	(*index)++;
	while (line[*index] != '\"')
	{
		if (line[*index] == '\\' && line[*index + 1] == '\"')
		{
			tmp = ft_strnjoin_free(tmp, &line[*index], 1);
			(*index)++;
		}
		tmp = ft_strnjoin_free(tmp, &line[*index], 1);
		(*index)++;
	}
	tmp = ft_strnjoin_free(tmp, &line[*index], 1);
	(*index)++;
	return (tmp);
}
