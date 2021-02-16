#include "minishell.h"

static int	get_child_process_result(int status)
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
		process_pipes(piped_chunks, 0,
							ft_count_strs((const char**)piped_chunks), envp);
		ft_free_split(piped_chunks);
		exit(0);
	}
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
	return ;
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

void		process_one_command(char *command, t_list *envp)
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
