
// #include "minishell.h"

// // static int	get_child_process_result(int status)
// // {
// // 	if (WIFEXITED(status))
// // 		return (WEXITSTATUS(status));
// // 	if (WIFSIGNALED(status))
// // 		return (EXIT_INVALID + WTERMSIG(status));
// // 	return (-1);
// // }

// // // void	hoge(int fds[2])
// // // {
// // // 	close(fds[0]);
// // // 	close(fds[1]);
// // // }

// // int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
// // {
// // 	int		fds[2];

// // 	if (i == chunks_num - 1)
// // 	{
// // 		exec_command_chunk(piped_chunks[0], envp);
// // 		return (0);
// // 	}
// // 	pipe(fds);
// // 	g_pid = fork();
// // 	if (g_pid == 0) // 子プロセスの場合。パイプを stdout に dup して、再帰し、次の fork で親になった側が右から i + 1 番目を実行。
// // 	{
// // 		close(fds[0]);
// // 		close(STDOUT_FILENO); // TODO: エラー処理
// // 		dup2(fds[1], STDOUT_FILENO);
// // 		close(fds[1]);
// // 		process_pipes(piped_chunks, i + 1, chunks_num, envp);
// // 	}
// // 	else
// // 	{	// 親プロセスの場合。stdin に dup をし、右から i 番目のコマンドを実行。
// // 		close(fds[1]);
// // 		close(STDIN_FILENO); // 実験中
// // 		dup2(fds[0], STDIN_FILENO);
// // 		close(fds[0]);
// // 		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp);
// // 	}
// // 	// hoge(fds);
// // 	return (0);
// // }



// static int	get_child_process_result(int status)
// {
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	if (WIFSIGNALED(status))
// 		return (EXIT_INVALID + WTERMSIG(status));
// 	return (-1);
// }

// void	ignore_signal(int sig)
// {
// 	(void)sig;
// 	return ;
// }

// static int	wait_parent(pid_t pids[2], int fds[2])
// {
// 	int status;

// 	close(fds[0]);
// 	close(fds[1]);
// 	waitpid(pids[0], &status, 0);
// 	waitpid(pids[1], NULL, 0);
// 	return (get_child_process_result(status));
// }

// int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
// {
// 	int		fds[2];
// 	pid_t	pids[2];

// 	if (i == chunks_num - 1)
// 	{
// 		exec_command_chunk(piped_chunks[i], envp);
// 		return (0);
// 	}
// 	if (pipe(fds) == ERROR)
// 		exit_err_msg(strerror(errno));
// 	pids[0] = fork();
// 	if (pids[0] == ERROR)
// 		exit_err_msg(strerror(errno));
// 	if (pids[0] == 0) // 子プロセスの場合。パイプを stdout に dup して、再帰し、次の fork で親になった側が右から i + 1 番目を実行。
// 	{
// 		close(fds[1]);
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
// 		exit(process_pipes(piped_chunks, i + 1, chunks_num, envp));
// 	}
// 	signal(SIGINT, ignore_signal);
// 	pids[1] = fork();
// 	if (pids[1] == ERROR)
// 		exit_err_msg(strerror(errno));
// 	if (pids[1] == 0)
// 	{
// 		close(fds[0]);
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		exec_command_chunk(piped_chunks[0], envp);
// 		exit(0);
// 	}
// 	g_last_exit_status = wait_parent(pids, fds); // TODO: なぜ分けて入れている？
// 	return (0);
// }

// void		in_process(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(2, "\n", 1);
// 	}
// 	if (sig == SIGQUIT)
// 	{
// 		write(2, "Quit: 3\n", 8);
// 	}
// }
// // コマンドを実行するたびに、このように親と子でプロセスが分かれる。
// // static int		fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
// // static void	fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
// // 													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
// // {
// // 	int		ret;
// // 	int		status;

// // 	g_pid = fork(); // なぜ、このタイミングで fork が必要なのか。
// // 	if (g_pid == ERROR)
// // 		exit_err_msg(strerror(errno));
// // 	// シグナル処理？
// // 	if (g_pid == 0)
// // 	{
// // 		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
// // 		exit(ret);
// // 	}
// // 	wait(&status);
// // 	g_last_exit_status = get_child_process_result(status);
// // 	return ;
// // }

// static void	fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
// 													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
// {
// 	int		ret;
// 	int		status;
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == ERROR)
// 		exit_err_msg(strerror(errno));
// 	signal(SIGINT, in_process);
// 	if (!piped_chunks[1])
// 		signal(SIGQUIT, in_process);
// 	else
// 		signal(SIGQUIT, ignore_signal);
// 	if (pid == 0)
// 	{
// 		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
// 		exit(ret);
// 	}
// 	wait(&status);
// 	g_last_exit_status = get_child_process_result(status);
// 	return ;
// }

// static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
// {
// 	char	**chunk_words;

// 	chunk_words = split_command_line(chunks[0]);
// 	if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
// 		exec_command_chunk(chunks[0], envp);
// 	else	
// 		fork_exec_commands(chunks, envp); // こいつがここでなんかやり方汚い。１つだけ受け取るようにできないか？
// }

// void	process_one_command(char *command, t_list *envp) // ; 区切りで１つずつ渡ってくる
// {
// 	char	**piped_chunks;
// 	size_t	chunks_num;

// 	piped_chunks = ft_split_skipping_quotes(command, '|');
// 	if (!piped_chunks)
// 		exit_err_msg(MALLOC_ERR);
// 	chunks_num = ft_count_strs((const char**)piped_chunks);
// 	if (chunks_num == 1)
// 		exec_no_pipe_chunk(piped_chunks, envp);
// 	else if (chunks_num >= 2)
// 		fork_exec_commands(piped_chunks, envp);
// 	ft_free_split(piped_chunks);
// }


#include "minishell.h"

void		sig_ignore(int sig)
{
	(void)sig;
	return ;
}

static int	get_child_process_result(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (EXIT_INVALID + WTERMSIG(status));
	return (-1);
}

// void	hoge(int fds[2])
// {
// 	close(fds[0]);
// 	close(fds[1]);
// }

// int			process_pipes(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
// {
// 	int		fds[2];

// 	if (i == chunks_num - 1)
// 	{
// 		exec_command_chunk(piped_chunks[0], envp);
// 		return (0);
// 	}
// 	pipe(fds);
// 	g_pid = fork();
// 	if (g_pid == 0) // 子プロセスの場合。パイプを stdout に dup して、再帰し、次の fork で親になった側が右から i + 1 番目を実行。
// 	{
// 		close(fds[0]);
// 		close(STDOUT_FILENO); // TODO: エラー処理
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		process_pipes(piped_chunks, i + 1, chunks_num, envp);
// 	}
// 	else
// 	{	// 親プロセスの場合。stdin に dup をし、右から i 番目のコマンドを実行。
// 		close(fds[1]);
// 		close(STDIN_FILENO); // 実験中
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
// 		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp);
// 	}
// 	// hoge(fds);
// 	return (0);
// }

// コマンドを実行するたびに、このように親と子でプロセスが分かれる。
// static int		fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
// static void	fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
// 													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
// {
// 	int		ret;
// 	int		status;

// 	g_pid = fork(); // なぜ、このタイミングで fork が必要なのか。
// 	if (g_pid == ERROR)
// 		exit_err_msg(strerror(errno));
// 	// シグナル処理？
// 	if (g_pid == 0)
// 	{
// 		ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
// 		exit(ret);
// 	}
// 	wait(&status);
// 	g_last_exit_status = get_child_process_result(status);
// 	return ;
// }

void	set_and_close_pipe(int pipe_fd[][2], size_t index, size_t chunks_num)
{
	if (index == 0)
	{
		dup2(pipe_fd[index][1], 1);
		close(pipe_fd[index][0]);
		close(pipe_fd[index][1]);
	}
	else if (index == chunks_num - 1)
	{
		dup2(pipe_fd[index - 1][0], 0);
		close(pipe_fd[index - 1][0]);
		close(pipe_fd[index - 1][1]);
	}
	else
	{
		dup2(pipe_fd[index - 1][0], 0);
		dup2(pipe_fd[index][1], 1);
		close(pipe_fd[index - 1][0]);
		close(pipe_fd[index - 1][1]);
		close(pipe_fd[index][0]);
		close(pipe_fd[index][1]);
	}
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
	if (g_pid == 0) // 子プロセスの場合。パイプを stdout に dup して、再帰し、次の fork で親になった側が右から i + 1 番目を実行。
	{
		close(fds[0]);
		close(STDOUT_FILENO); // TODO: エラー処理
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		process_pipes(piped_chunks, i + 1, chunks_num, envp);
	}
	else
	{	// 親プロセスの場合。stdin に dup をし、右から i 番目のコマンドを実行。
		close(fds[1]);
		close(STDIN_FILENO); // 実験中
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp);
	}
	// hoge(fds);
	return (0);
}

// int			has_pipe_child(char **piped_chunks, size_t i, size_t chunks_num, t_list *envp)
// {
// 	int		fds[2];

// 	if (i == chunks_num - 1)
// 	{
// 		exec_command_chunk(piped_chunks[0], envp);
// 		return (0);
// 	}
// 	pipe(fds);
// 	g_pid = fork();
// 	if (g_pid == 0) // 子プロセスの場合。パイプを stdout に dup して、再帰し、次の fork で親になった側が右から i + 1 番目を実行。
// 	{
// 		close(fds[0]);
// 		close(STDOUT_FILENO); // TODO: エラー処理
// 		dup2(fds[1], STDOUT_FILENO);
// 		close(fds[1]);
// 		process_pipes(piped_chunks, i + 1, chunks_num, envp);
// 	}
// 	else
// 	{	// 親プロセスの場合。stdin に dup をし、右から i 番目のコマンドを実行。
// 		close(fds[1]);
// 		close(STDIN_FILENO); // 実験中
// 		dup2(fds[0], STDIN_FILENO);
// 		close(fds[0]);
// 		exec_command_chunk(piped_chunks[(chunks_num - 1) - i], envp);
// 	}
// 	// hoge(fds);
// 	return (0);
// }

static void	fork_exec_commands(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
{
	int		ret;
	int		status;
	pid_t	pid;

	pid = fork(); // なぜ、このタイミングで fork が必要なのか。
	// TODO: おそらく fork 要らない。こうだいさんのhas_no_pipe みたいなのと見比べる。
	if (pid == ERROR)
		exit_err_msg(strerror(errno));
	// シグナル処理？
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
	int		flag;

	size_t	index;
	index = 0;

	flag = 1;
	(void)piped_chunks;
	while (index < chunks_num)
	{
		if (wait(&status) == last_pid)
		{
			if (status == 2)
				status = 130 * 256;
			if (status == 3)
				status = 131 * 256;
			g_last_exit_status = status;
		}
		if (flag && (status == 2 || status == 130 * 256))
		{
			write(2, "\n", 1);
			flag = 0; // 改行を１回で済ませるため
		}
		if (flag && (status == 3 || status == 131 * 256))
		{
			write(2, "Quit: 3\n", 8);
			flag = 0;
		}
		index++;
	}
}


static void has_pipe(char **piped_chunks, t_list *envp) // ここに入るのは２パターン。1) パイプなし、not reproduction
													// 2) パイプありは必ず。つまり、パイプなしでreproduction の時は特別、入らない。
{
	// int		ret;
	// int		status;
	pid_t	pid;
	int		pipe_fd[100000][2];

	// g_pid = fork(); // なぜ、このタイミングで fork が必要なのか。
	// if (g_pid == ERROR)
	// 	exit_err_msg(strerror(errno));
	// シグナル処理？
	size_t	index;
	index = 0;
	const size_t chunks_num = ft_count_strs((const char**)piped_chunks);
	while (index < chunks_num)
	{
		if (index != chunks_num - 1)
			pipe(pipe_fd[index]);
		signal(SIGINT, sig_ignore);
		signal(SIGQUIT, sig_ignore);	// signal(SITINT, )
		pid = fork();
		if (pid == 0)
		{
			set_and_close_pipe(pipe_fd, index, chunks_num);
			exec_command_chunk(piped_chunks[index], envp);
			// has_pipe_child(piped_chunks, index, chunks_num, envp);
		}
		if (index != 0)
		{
			close(pipe_fd[index - 1][0]);
			close(pipe_fd[index - 1][1]);
		}
		index++;
	}
	// if (g_pid == 0)
	// {
	// 	ret = process_pipes(piped_chunks, 0, ft_count_strs((const char**)piped_chunks), envp);
	// 	exit(ret);
	// }
	wait_children(piped_chunks, chunks_num, pid);
	// wait(&status);
	// g_last_exit_status = get_child_process_result(status);
	// return ;
}


// TODO: パイプがない時も、このパイプありの時と共通の処理になってしまっている。
// -> 別の処理を用意する必要あり。

static void	exec_no_pipe_chunk(char **chunks, t_list *envp)
{
	char	**chunk_words;
	char	*tmp;

	chunk_words = split_command_line(chunks[0]);
	if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
	{
		ft_free_split(chunk_words);
		tmp = ft_strdup(chunks[0]);
		ft_free_split(chunks);
		exec_command_chunk(tmp, envp);
	}
	else	
	{
		ft_free_split(chunk_words);
		fork_exec_commands(chunks, envp); // こいつがここでなんかやり方汚い。１つだけ受け取るようにできないか？
	}
}

// void	process_one_command(char *command, t_list *envp) // ; 区切りで１つずつ渡ってくる
// {
// 	char	**piped_chunks;
// 	size_t	chunks_num;

// 	piped_chunks = ft_split_skipping_quotes(command, '|');
// 	chunks_num = ft_count_strs((const char**)piped_chunks);
// 	if (chunks_num == 1)
// 		exec_no_pipe_chunk(piped_chunks, envp);
// 	else if (chunks_num >= 2)
// 		fork_exec_commands(piped_chunks, envp);
// 	ft_free_split(piped_chunks);
// }

void	process_one_command(char *command, t_list *envp) // ; 区切りで１つずつ渡ってくる
{
	char	**piped_chunks;
	size_t	chunks_num;

	piped_chunks = ft_split_skipping_quotes(command, '|');
	chunks_num = ft_count_strs((const char**)piped_chunks);

	int	stdout_fd;
	int	stdin_fd;
	stdin_fd = dup(STDIN_FILENO);	// 引数: oldfd
	stdout_fd = dup(STDOUT_FILENO);	// 元の標準入力、標準出力に、未使用の若い番号を割り振っている

	if (chunks_num == 1)
		exec_no_pipe_chunk(piped_chunks, envp);
	else if (chunks_num >= 2)
		has_pipe(piped_chunks, envp);

	dup2(stdout_fd, STDOUT_FILENO);	// 先ほど割り振った番号を、再度標準入力 / 出力に戻している。
	dup2(stdin_fd, STDIN_FILENO);
	close(stdout_fd);
	close(stdin_fd);

	ft_free_split(piped_chunks);
}
