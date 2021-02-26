/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:35 by monoue            #+#    #+#             */
/*   Updated: 2021/02/26 13:25:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	get_child_process_result(int status)
int	get_child_process_result(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_INVALID + WTERMSIG(status));
	// return ();
	return (ERROR);
	// return (g_last_exit_status);
	// return (EXIT_SUCCESS);
}

static void	fork_exec_commands(char **piped_chunks, t_list *envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		exit_err_msg(strerror(errno));
	if (pid == 0)
	{
		process_pipes(piped_chunks, 0,
							ft_count_strs((const char**)piped_chunks), envp);
		ft_free_split(piped_chunks);
		exit(EXIT_SUCCESS);
		// exit(g_last_exit_status);
	}
	g_pid = pid;
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
}

static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
{
	char	**chunk_words;

	chunk_words = split_command_line(chunks[0]);
	if (is_reproduction(chunk_words[0]))
		exec_command_chunk(chunks[0], envp, false);
	else
		fork_exec_commands(chunks, envp);
	ft_free_split(chunk_words);
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
		exec_no_pipe_chunk(piped_chunks, envp);
	else if (chunks_num >= 2)
		has_pipe(piped_chunks, envp, chunks_num);
	ft_free_split(piped_chunks);
}
