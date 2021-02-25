/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 13:11:49 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			get_default_fd_num(t_type redirection_type)
{
	if (redirection_type == TYPE_INPUT)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int			get_fd_num(char *redirection_str, t_type redirection_type)
{
	if (!ft_isdigit(redirection_str[0]))
		return (get_default_fd_num(redirection_type));
	if (!str_is_within_int(redirection_str))
		return (OVER_INT_MAX);
	return (ft_atoi(redirection_str));
}

t_redirection_set	*make_redirection_set(char **elements, bool *err_fd_open)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	char				*filename;

	set = NULL;
	new = ft_calloc(1, sizeof(t_redirection_set));
	if (!new)
		exit_err_msg(MALLOC_ERR);
	new->type = get_redirection_type(elements[0]);
	new->designated_fd = get_fd_num(elements[0], new->type);
	*err_fd_open = (new->designated_fd == 2);
	filename = elements[1];
	if (str_is_quoted(filename))
		new->filename = ft_strndup(&filename[1], ft_strlen(filename) - 2);
	else
		new->filename = ft_strdup(filename);
	lstadd_back(&set, new);
	return (set);
}
