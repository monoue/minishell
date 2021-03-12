/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:05 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 15:47:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	handle_exec_error(const char *command)
{
	if (errno == ENOENT)
		exit_bash_err_msg(command, strerror(ENOENT), 127);
	if (errno == EACCES)
		exit_bash_err_msg(command, strerror(EISDIR), 126);
	if (errno == ENOTDIR)
		exit_bash_err_msg(command, strerror(ENOTDIR), 126);
	exit_bash_err_msg(command, NO_COMMANDS_ERR, 127);
}
