/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:44:43 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 14:44:44 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipes(char **piped_chunks, size_t i, size_t chunks_num,
																t_list *envp)
{
	int		fds[2];

	if (i == chunks_num - 1)
	{
		exec_command_chunk(piped_chunks[0], envp, true);
		return ;
	}
	pipe(fds);
	if ((g_pid = fork()) == 0)
	{
		close(fds[0]);
		close(STDOUT_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		process_pipes(piped_chunks, i + 1, chunks_num, envp);
	}
	else
	{
		close(fds[1]);
		close(STDIN_FILENO);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp, true);
	}
	ft_free_split(piped_chunks);
}
