/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:44:55 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 07:05:15 by monoue           ###   ########.fr       */
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

int			set_redirection(t_redirection_set *set, t_fd *fds)
{
	int				file_fd;
	int				*p_fd;
	int				std_fd;
	const t_type	type = set->type;

	file_fd = open(set->filename, get_open_flags(type), OPEN_MODE);
	if (file_fd == ERROR || is_bad_fd(set->fd))
	{
		if (file_fd == ERROR)
		{
			DS("hoge");
			put_bash_err_msg(set->filename, strerror(errno));

		}
		else
			put_bad_fd_message(set->fd);
		g_last_exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	if (type == TYPE_INPUT)
		p_fd = &(fds->input);
	else
		p_fd = &(fds->output);
	std_fd = dup(*p_fd);
	close(*p_fd);
	dup2(file_fd, set->fd);
	close(file_fd);
	*p_fd = std_fd;
	return (SUCCESS);
}
