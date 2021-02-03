
#include "../minishell.h"

static int	get_child_process_result_from(int status) // 分析
{
	int	result;

	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		result = EXIT_INVALID + SIGINT;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		result = EXIT_INVALID + SIGQUIT;
	return (result);
}

int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num)
{
	pid_t	pid;
	int		fds[2];

	if (i == chunks_num - 1)
	{
		exec_command_chunk(piped_chunks[0]);
		return (0);
	}
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		process_pipes(piped_chunks, i + 1, chunks_num);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		exec_command_chunk(piped_chunks[(chunks_num - 1) - i]);
	}
	return (0);
}

static int		fork_exec_commands(char **piped_chunks) // ここに入るのは２パターン。1) パイプなし、not reproduction
													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork(); // なぜ、このタイミングで fork が必要なのか。
	if (pid == ERROR)
		exit_fatal();
	// シグナル処理？
	if (pid == 0)
	{
		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks));
		exit(ret);
	}
	wait(&status);
	return (get_child_process_result_from(status)); // ??
}

static void	exec_no_pipe_chunk(char **chunks)
{
	char	**chunk_words;

	chunk_words = space_and_tab_split(chunks[0]);
	if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
		exec_command_chunk(chunks[0]);
	else	
		fork_exec_commands(chunks); // こいつがここでなんかやり方汚い。１つだけ受け取るようにできないか？
}

void	process_one_command(char *command) // ; 区切りで１つずつ渡ってくる
{
	char	**piped_chunks;
	size_t	chunks_num;

	piped_chunks = ft_split(command, '|');
	// エラー処理
	chunks_num = ft_count_strs((const char**)piped_chunks);
	if (chunks_num == 1)
		exec_no_pipe_chunk(piped_chunks);
	else if (chunks_num >= 2)
		fork_exec_commands(piped_chunks);
	ft_free_split(piped_chunks);
}
