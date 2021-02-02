#include "../minishell.h"

static int	get_child_process_result_from(int status) // 分析
{
	int	result;

	if (WIFEXITED(status))
	{
		result = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		result = EXIT_INVALID + SIGINT;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		result = EXIT_INVALID + SIGQUIT;
	}
	return (result);
}

// void	exec_cmd(t_chunk *chunk, t_list *envp)
// {
// 	pid_t		pid;
// 	bool		is_pipe_open;
// 	int			flag;

// 	is_pipe_open = false;
// 	if (is_type_pipe(chunk) || is_type_pipe(chunk->prev))
// 	{
// 		is_pipe_open = true;
// 		if (pipe(chunk->fds) == ERROR)
// 			exit_fatal();
// 	}
// 	flag = pipe_or_not_pipe(chunk);//ここはPIPEあるかない、または builtinsではあるかないを確認して、FLAG＝０場合はコマンドを移動して、FLAG=１場合はFORKに行く
// 	if (flag == 0) 
// 		no_pipe(chunk, envp);//builtins
// 	else
// 	{
// 		pid = fork();
// 		if (pid == ERROR)
// 			exit_fatal();
// 		if (pid == 0)
// 			do_child(chunk, envp);
// 		else
// 			do_parent(chunk, pid, is_pipe_open);
// 	}
// 	flag = 0;
// }

// void	exec_cmds(t_chunk *ptr, t_list *envp)
// {
// 	t_redirection_set	*tmp;

// 	tmp = ptr;
// 	while (tmp)
// 	{
// 		if (ft_strequal("cd", tmp->argv[0]))
// 		{
// 			if (tmp->size == 1)
// 				chdir("~");
// 			else if (chdir(tmp->argv[1]) == ERROR)
// 			{
// 				perror("cd: "); // 本物と一致しているかチェック
// 			}
// 		}
// 		else
// 			exec_cmd(tmp, envp);
// 		tmp = tmp->next;	
// 	}
// }
// void	clear_leaks(t_chunk *ptr)
// {
// 	t_redirection_set	*tmp;
// 	size_t	index;

// 	while (ptr)
// 	{
// 		tmp = ptr->next;
// 		// index = 0;
// 		// TODO: ft_free_split に置き換えて試す。
// 		ft_free_split(ptr->argv);
// 		// while (index < ptr->size)
// 		// {
// 		// 	free(ptr->argv[index]);
// 		// 	index++;
// 		// }
// 		// free(ptr->argv);
// 		// ここまで
// 		SAFE_FREE(ptr);
// 		ptr = tmp;
// 	}
// 	ptr = NULL;
// }





// 元の
// void	make_set_list(t_redirection_set **set, char **elements, size_t elements_num)
// {
// 	t_redirection_set	*new;
// 	size_t				index;

// 	index = 0;
// 	while (index < elements_num)
// 	{
// 		new = ft_calloc(1, sizeof(t_redirection_set));
// 		if (!new)
// 			exit_fatal();
// 		new->word = ft_strdup(elements[index]); // 各要素の代入 (Substitution of each element)
// 		if (index == 0)
// 			new->type = NULL; // first, とかを enum で作っても良い。
// 		else
// 			new->type = get_redirection_type(elements[index - 1]);
// 		lstadd_back(set, new); // libft と名前が重複するため
// 		index += 2;
// 	}
// }


// void	exec_command_chunk(char *command_chunk)
// {
// 	t_redirection_set	*set;
// 	t_fd				fds;
// 	size_t				index;
// 	size_t				strs_num;
// 	char				**elements;

// 	elements = split_cmd_line(command_chunk);
// 	strs_num = ft_count_strs((const char**)elements);
// 	if (!strs_num)
// 		return ;
// 	set_fds(&fds);
// 	set = NULL; // 返り値で作った方が綺麗な感じはする。まあ、動いてからでいいや。
// 	make_set_list(&set, elements, strs_num);
// }


// いきなり flags で構造体に突っ込んでも良いような…？
// エラー処理を返り値で処理する必要があるかも
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
			// redirection_i = index;
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
		DS(argv[index]);
		index++;
	}
	exec_command_argv(argv); // 各コマンドに入れるだけ
}

// pipe があるのかどうかを…渡してあげる？ それとも、この中でスプリット？
int		exec_pipe_command(char **piped_chunks, int i, size_t chunks_num) // この関数が不明
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
			// exec
		}
	}
	return (0);
	// int		fds[2];
	// pid_t	pids[2];

	// if (!piped_chunks[1])
	// {
	// 	// ここに渡すため、スプリットが必要
	// 	exec_split();
	// 	return ;
	// }
	// if (pipe(fds) == ERROR)
	// 	exit_fatal();
	// pids[0] = fork();
	// if (pids[0] == ERROR)
	// 	exit_fatal();
	// if (pids[0] == 0)
	// {
	// 	close_and_dup(fds, STDIN_FILENO);
	// 	exit(exec_pipe_command(&piped_chunks[1])); // 再帰的に実行
	// }


	// pids[1] = fork();
	// if (pids[1] == ERROR)
	// 	exit_fatal();
	// if (pids[1] == 0)
	// {
	// 	close_and_dup(fds, STDOUT_FILENO);
	// 	exit(exec_command_chunk(piped_chunks[0]));
	// }
	// return (parent_wait(pids[0], pids[1], fds));

}

// int		fork_exec_commands(char **chunk_words)
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
		fork_exec_commands(chunks); // こいつがここでなんかやり方汚い。１つだけ受け取るようにできないのか？
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
		// chunk_words = space_and_tab_split(piped_chunks[0]);
		// // エラー処理
		// if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
		// 	// それぞれ、exit のナンバーを後ほど受け取る
		// 	exec_command_chunk(piped_chunks[0]);
		// else	
		// 	fork_exec_commands(piped_chunks);
	else if (chunks_num >= 2)
		fork_exec_commands(piped_chunks);
	ft_free_split(piped_chunks);
}
// void	process_one_command(char *command) // ; 区切りで１つずつ渡ってくる
// {
// 	char	**piped_chunks;
// 	size_t	chunks_num;
// 	char	**chunk_words;

// 	piped_chunks = ft_split(command, '|');
// 	// エラー処理
// 	chunks_num = ft_count_strs((const char **)piped_chunks);
// 	size_t	index = 0;
// 	while (piped_chunks[index])
// 	{
// 		// DS(piped_chunks[index]);
// 		index++;
// 	}
// 	// DSZ(chunks_num);
// 	// if (chunks_num == 1)
// 	// {
// 		chunk_words = space_and_tab_split(piped_chunks[0]);

// 	index = 0;
// 	while (chunk_words[index])
// 	{
// 		DS(chunk_words[index]);
// 		index++;
// 	}
	
// 		// エラー処理
// 		// if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
// 		// 	// それぞれ、exit のナンバーを後ほど受け取る
// 		// 	exec_command_chunk(piped_chunks[0]);
// 		// else	
// 		// 	fork_exec_commands(piped_chunks);
// 	// }
// 	// else if (chunks_num >= 2)
// 	// 	fork_exec_commands(piped_chunks);
// 	// ft_free_split(piped_chunks);
// }

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

// void	test_process_command_line(char *line)
// {
// 	ft_putstr(PROMPT);
// 	// if (get_next_line(STDIN_FILENO, &line) == ERROR)
// 	// 	exit_err_msg(MALLOC_ERR);
// 	// if (is_invalid_syntax(line)) // 未完成
// 	// {
// 	// 	SAFE_FREE(line);
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// 環境変数をここで整える
// 	// コメントもここで削る
// 	exec_one_line(line);
// }
// int main()
// {
// 	char *str = "hoge fuga \t | hoge; peko | poko";
// 	test_process_command_line(str);
// }