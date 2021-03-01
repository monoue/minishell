/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:12 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 13:25:15 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** duplicates original stdin and stdout fds
*/

void	set_fds(t_fd *fds)
{
	fds->input = dup(STDIN_FILENO);
	fds->output = dup(STDOUT_FILENO);
}
