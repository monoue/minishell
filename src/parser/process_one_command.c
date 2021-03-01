/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:35 by monoue            #+#    #+#             */
/*   Updated: 2021/03/01 11:22:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_child_process_result(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_INVALID + WTERMSIG(status));
	return (ERROR);
}

static void	exec_no_pipe_chunk(char *chunk, t_list *envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		exit_err_msg(strerror(errno));
	if (pid == 0)
	{
		exec_command_chunk(chunk, envp, true);
		exit(EXIT_SUCCESS);
	}
	g_pid = pid;
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
}

void		process_one_command(char *command, t_list *envp)
{
	char	**piped_chunks;
	size_t	chunks_num;

	piped_chunks = ft_split_skipping_quotes(command, '|');
	if (!piped_chunks)
		exit_err_msg(MALLOC_ERR);
	chunks_num = ft_count_strs((const char**)piped_chunks);
	if (chunks_num == 1)
		exec_no_pipe_chunk(piped_chunks[0], envp);
	else if (chunks_num >= 2)
		has_pipe(piped_chunks, envp, chunks_num);
	ft_free_split(piped_chunks);
}
