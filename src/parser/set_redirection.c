/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:44:55 by monoue            #+#    #+#             */
/*   Updated: 2021/02/18 18:08:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_if_filename_not_set(char c)
{
	if (c == '\0')
		exit_bash_err_msg("", strerror(ENOENT), EXIT_FAILURE);
}

static int	get_open_flags(t_type type)
{
	if (type == TYPE_INPUT)
		return (O_RDONLY);
	if (type == TYPE_OUTPUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == TYPE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (ERROR);
}

void		set_redirection(t_redirection_set *set, t_fd *fds)
{
	int				file_fd;
	int				*p_fd;
	int				std_fd;
	const t_type	type = set->type;

	exit_if_filename_not_set(set->filename[0]);
	file_fd = open(set->filename, get_open_flags(type), OPEN_MODE);
	if (file_fd == ERROR)
		exit_err_msg(strerror(errno));
	if (type == TYPE_INPUT)
	{
		p_fd = &(fds->input);
		std_fd = dup(*p_fd);
		exit_if_closing_fd_error(*p_fd);
		dup2(file_fd, STDIN_FILENO);
	}
	else
	{
		p_fd = &(fds->output);
		std_fd = dup(*p_fd);
		exit_if_closing_fd_error(*p_fd);
		dup2(file_fd, STDOUT_FILENO);
	}
	exit_if_closing_fd_error(file_fd);
	*p_fd = std_fd;
}
