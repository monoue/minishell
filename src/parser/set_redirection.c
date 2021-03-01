/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:44:55 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 08:09:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	is_bad_fd(int fd)
{
	if (fd == OVER_INT_MAX)
		return (true);
	return (fd > UCHAR_MAX);
}

static void	put_bad_fd_message(int fd)
{
	const char	*out_of_range = "file descriptor out of range";
	const char	*bad_fd = "Bad file descriptor";
	char		*num_str;

	if (fd == OVER_INT_MAX)
		put_bash_err_msg(out_of_range, bad_fd);
	else
	{
		num_str = ft_itoa(fd);
		put_bash_err_msg(num_str, bad_fd);
		SAFE_FREE(num_str);
	}
}

static void	put_redirection_error_message(int file_fd, t_redirection_set *set)
{
	if (file_fd == ERROR)
		put_bash_err_msg(set->filename, strerror(errno));
	else
		put_bad_fd_message(set->designated_fd);
}

int			set_redirection(t_redirection_set *set, t_fd *fds)
{
	int				file_fd;
	const t_type	type = set->type;
	const int		designated_fd = set->designated_fd;
	const char		*filename = set->filename;

	file_fd = open(filename, get_open_flags(type), OPEN_MODE);
	if (file_fd == ERROR || is_bad_fd(designated_fd))
	{
		put_redirection_error_message(file_fd, set);
		g_last_exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	close(designated_fd);
	if (type == TYPE_INPUT)
		dup2(fds->input, designated_fd);
	else
		dup2(fds->output, designated_fd);
	dup2(file_fd, designated_fd);
	close(file_fd);
	return (SUCCESS);
}
