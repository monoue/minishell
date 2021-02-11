
#include "minishell.h"

static int	get_child_process_result(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_INVALID + WTERMSIG(status));
	return (-1);
}

int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
{
	int		fds[2];

	if (i == chunks_num - 1)
	{
		exec_command_chunk(piped_chunks[0], envp);
		return (0);
	}
	pipe(fds);
	g_pid = fork();
	if (g_pid == 0)
	{
		close(fds[0]);
		close(STDOUT_FILENO); // TODO: エラー処理
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		process_pipes(piped_chunks, i + 1, chunks_num, envp);
	}
	else
	{
		close(fds[1]);
		close(STDIN_FILENO); // 実験中
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp);
	}
	return (0);
}

// static int		fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
static void	fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
{
	int		ret;
	int		status;

	g_pid = fork(); // なぜ、このタイミングで fork が必要なのか。
	if (g_pid == ERROR)
		exit_err_msg(strerror(errno));
	// シグナル処理？
	if (g_pid == 0)
	{
		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
		exit(ret);
	}
	wait(&status);
	g_last_exit_status = get_child_process_result(status);
	return ;
}

static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
{
	char	**chunk_words;

	chunk_words = split_command_line(chunks[0]);
	if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
		exec_command_chunk(chunks[0], envp);
	else	
		fork_exec_commands(chunks, envp); // こいつがここでなんかやり方汚い。１つだけ受け取るようにできないか？
}

void	process_one_command(char *command, t_list *envp) // ; 区切りで１つずつ渡ってくる
{
	char	**piped_chunks;
	size_t	chunks_num;

	piped_chunks = ft_split_skipping_quotes(command, '|');
	chunks_num = ft_count_strs((const char**)piped_chunks);
	if (chunks_num == 1)
		exec_no_pipe_chunk(piped_chunks, envp);
	else if (chunks_num >= 2)
		fork_exec_commands(piped_chunks, envp);
	ft_free_split(piped_chunks);
}
