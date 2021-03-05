/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/05 16:48:18 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exec_command_argv(char **argv, t_list *envp, bool pipe_child)
{
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp, pipe_child);
	else
		exec_path_command(argv, envp);
}
