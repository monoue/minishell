/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_redirection_fds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 06:42:00 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** resets fds so that the outcome comes out from the pipe
*/

void	reset_redirection_fds(t_fd *fds)
{
	dup2(fds->output, STDOUT_FILENO);
	dup2(fds->input, STDIN_FILENO);
	close(fds->output);
	close(fds->input);
}
