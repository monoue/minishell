/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:43 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 06:35:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_ignore(int sig)
{
	(void)sig;
	return ;
}

static void	close_pipes(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

/*
** First, connects stdout to the first command's input.
** Since second time, connects stdin to last command's output and
** stdout to the current command's input so that it can take last command's
** output.
** At the last time, connects stdin to last command's output so that the last
** command can take last command's output from stdin.
*/

static void	set_and_close_pipe(int pipe_fd[][2], size_t index,
															size_t chunks_num)
{
	if (index == 0)
	{
		dup2(pipe_fd[index][1], STDOUT_FILENO);
		close_pipes(pipe_fd[index]);
	}
	else if (index == chunks_num - 1)
	{
		dup2(pipe_fd[index - 1][0], STDIN_FILENO);
		close_pipes(pipe_fd[index - 1]);
	}
	else
	{
		dup2(pipe_fd[index - 1][0], STDIN_FILENO);
		dup2(pipe_fd[index][1], STDOUT_FILENO);
		close_pipes(pipe_fd[index - 1]);
		close_pipes(pipe_fd[index]);
	}
}

static void	wait_children(size_t chunks_num, int last_pid)
{
	int		status;
	bool	flag;
	size_t	index;

	index = 0;
	flag = true;
	while (index < chunks_num)
	{
		if (wait(&status) == last_pid)
		{
			if (WIFEXITED(status))
				g_last_exit_status = (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				g_last_exit_status = (EXIT_INVALID + WTERMSIG(status));
		}
		if (flag && WIFSIGNALED(status))
		{
			flag = false;
			if (WTERMSIG(status) == 2)
				ft_putchar_err('\n');
			else if (WTERMSIG(status) == 3)
				ft_putendl_err("Quit: 3");
		}
		index++;
	}
}

void		has_pipe(char **piped_chunks, t_list *envp, size_t chunks_num)
{
	pid_t	pid;
	int		pipe_fd[chunks_num][2];
	size_t	index;

	index = 0;
	while (index < chunks_num)
	{
		if (index < chunks_num - 1)
			pipe(pipe_fd[index]);
		signal(SIGINT, sig_ignore);
		signal(SIGQUIT, sig_ignore);
		pid = fork();
		if (pid == 0)
		{
			set_and_close_pipe(pipe_fd, index, chunks_num);
			exec_command_chunk(piped_chunks[index], envp, true);
		}
		if (index > 0)
			close_pipes(pipe_fd[index - 1]);
		index++;
	}
	wait_children(chunks_num, pid);
}
