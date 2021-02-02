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

int		get_open_flags(t_type type)
{
	if (type == TYPE_INPUT)
		return (O_RDONLY);
	if (type == TYPE_OUTPUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == TYPE_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (ERROR);
}

void	set_redirection(t_redirection_set *set, t_fd *fds)
{
	int				flags;
	int				file_fd;
	int				*p_fd;
	int				std_fd;
	const t_type	type = set->type;

	flags = get_open_flags(type);
	file_fd = open(set->filename, flags, OPEN_MODE);
	if (file_fd == ERROR)
		exit_fatal();
	if (type == TYPE_INPUT)
		p_fd = &(fds->input);
	else
		p_fd = &(fds->output);
	std_fd = dup(*p_fd);
	close(*p_fd);
	if (type == TYPE_INPUT)
		dup2(file_fd, STDIN_FILENO);
	else
		dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	*p_fd = std_fd;
}

void	exec_command_argv(char **argv)
{
	extern char	**environ;
	char		*fullpath_cmd;

	if (ft_strequal(argv[0], "wc"))
		fullpath_cmd = ft_strjoin("/usr/bin/", argv[0]);
	else
		fullpath_cmd = ft_strjoin("/bin/", argv[0]);

	size_t	index = 0;
	while (argv[index])
	{
		DS(argv[index]);
		index++;
	}
	DS(fullpath_cmd);

	if (!fullpath_cmd)
		perror("");
	else if (execve(fullpath_cmd, argv, environ) == ERROR)
		perror("execve: ");
	SAFE_FREE(fullpath_cmd);
	exit(EXIT_SUCCESS);
}

// void	set_redirections(t_redirection_set *set)
// {
// 	t_redirection_set	*tmp;

// 	tmp = set;
// 	while (tmp)
// }

void	exec_command_chunk(char *command_chunk)
{
	t_redirection_set	*set;
	t_fd				fds;
	size_t	index;
	size_t	redirection_i;
	char	**argv;
	char	**chunk_words;

	chunk_words = space_and_tab_split(command_chunk);
	set = NULL;
	set_fds(&fds);
	index = 0;
	redirection_i = 0;
	while (chunk_words[index])
	{
		if (is_redirection_str(chunk_words[index]))	
		{
			set = make_redirection_list(&chunk_words[index]);
			break ;
		}
		index++;
	}
	redirection_i = index;
	while (set)	
	{
		set_redirection(set, &fds);
		set = set->next;
	}
	argv = ft_calloc(redirection_i + 1, sizeof(char*));
	index = 0;
	while (index < redirection_i)
	{
		argv[index] = chunk_words[index];
		index++;
	}
	exec_command_argv(argv);
}

int		exec_pipe_command(char **piped_chunks, int i, size_t chunks_num)
{
	pid_t			pid;
	int				fds[2];

	if (i == chunks_num - 1)
		exec_command_chunk(piped_chunks[0]);
	else
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
			exec_pipe_command(piped_chunks, i + 1, chunks_num);
		}
		else
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			exec_command_chunk(piped_chunks[(chunks_num - 1) - i]);
		}
	}
	return (0);
}

int		fork_exec_commands(char **piped_chunks) // ここに入るのは２パターン。1) パイプなし、not reproduction
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
		ret = exec_pipe_command(piped_chunks, 0, ft_count_strs((const char**)piped_chunks));
		exit(ret);
	}
	wait(&status);
	return (get_child_process_result_from(status)); // ??
}

void	exec_no_pipe_chunk(char **chunks)
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
	char	**chunk_words;
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

void	exec_one_line(char *line)
{
	char	**commands;	
	size_t	index;
	
	commands = ft_split(line, ';');
	index = 0;
	while (commands[index])	
	{
		process_one_command(commands[index]);
		index++;
	}
	ft_free_split(commands);
}

void	process_command_line(void)
{
	char	*line;

	ft_putstr(PROMPT);
	if (get_next_line(STDIN_FILENO, &line) == ERROR)
		exit_err_msg(MALLOC_ERR);
	// if (is_invalid_syntax(line)) // 未完成
	// {
	// 	SAFE_FREE(line);
	// 	exit(EXIT_FAILURE);
	// }
	// 環境変数をここで整える
	// コメントもここで削る
	exec_one_line(line);
}
