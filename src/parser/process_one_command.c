/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_one_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:35 by monoue            #+#    #+#             */
/*   Updated: 2021/03/01 13:48:57 by monoue           ###   ########.fr       */
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

bool	is_exit(char *word)
{
	const char	*reproductions[] = {
		"exit",
		NULL
	};
	size_t		index;
	char		*continuous_quotes_trimmed_str;

	continuous_quotes_trimmed_str = get_continuous_quotes_trimmed_str(word);
	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(continuous_quotes_trimmed_str, reproductions[index]))
		{
			SAFE_FREE(continuous_quotes_trimmed_str);
			return (true);
		}
		index++;
	}
	SAFE_FREE(continuous_quotes_trimmed_str);
	return (false);
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
		exit(g_last_exit_status);
	}
	g_pid = pid;
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
}

bool	is_output(char *word)
{
	const char	*reproductions[] = {
		"echo",
		"env",
		"pwd",
		NULL
	};
	size_t		index;
	char		*continuous_quotes_trimmed_str;

	continuous_quotes_trimmed_str = get_continuous_quotes_trimmed_str(word);
	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(continuous_quotes_trimmed_str, reproductions[index]))
		{
			SAFE_FREE(continuous_quotes_trimmed_str);
			return (true);
		}
		index++;
	}
	SAFE_FREE(continuous_quotes_trimmed_str);
	return (false);
}

static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
{
	char	**chunk_words;

	chunk_words = split_command_line(chunks[0]);
	if (is_reproduction(chunk_words[0]) && !is_output(chunk_words[0]))
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
