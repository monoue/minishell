#include "minishell.h"

void		sig_ignore(int sig)
{
	(void)sig;
	return ;
}

void	close_pipes(int pipe_fds[2])
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
void	set_and_close_pipe(int pipe_fd[][2], size_t index, size_t chunks_num)
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

int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
{
	int		fds[2];

	if (i == chunks_num - 1)
	{
		exec_command_chunk(piped_chunks[0], envp, true);
		return (0);
	}
	pipe(fds);
	g_pid = fork();
	if (g_pid == 0)
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
	return (0);
}

int	get_child_process_result(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_INVALID + WTERMSIG(status));
	return (-1);
}

static void	fork_exec_commands(char **piped_chunks, t_list *envp)
{
	int		ret;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == ERROR)
		exit_err_msg(strerror(errno));
	if (pid == 0)
	{
		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
		ft_free_split(piped_chunks);
		exit(ret);
	}
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
	return ;
}


void	wait_children(char **piped_chunks, size_t chunks_num, int last_pid)
{
	int		status;
	bool	flag;
	size_t	index;

	index = 0;
	flag = true;
	(void)piped_chunks;
	while (index < chunks_num)
	{
		if (wait(&status) == last_pid)
		{
			if (WIFSIGNALED(status))
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

static void has_pipe(char **piped_chunks, t_list *envp, size_t chunks_num)
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
	wait_children(piped_chunks, chunks_num, pid);
}

static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
{
	char	**chunk_words;
	char	*tmp;

	chunk_words = split_command_line(chunks[0]);
	if (is_reproduction(chunk_words[0]))
	{
		ft_free_split(chunk_words);
		tmp = ft_strdup(chunks[0]);
		exec_command_chunk(tmp, envp, false);
	}
	else	
	{
		ft_free_split(chunk_words);
		fork_exec_commands(chunks, envp);
	}
}

void	process_one_command(char *command, t_list *envp)
{
	char	**piped_chunks;
	size_t	chunks_num;

	piped_chunks = ft_split_skipping_quotes(command, '|');
	chunks_num = ft_count_strs((const char**)piped_chunks);
	if (chunks_num == 1)
		exec_no_pipe_chunk(piped_chunks, envp);
	else if (chunks_num >= 2)
		has_pipe(piped_chunks, envp, chunks_num);
	ft_free_split(piped_chunks);
}
