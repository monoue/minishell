#include "../minishell.h"


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

void	set_fds(t_fd *fds)
{
	fds->input = STDIN_FILENO;
	fds->output = STDOUT_FILENO;
}



// 元の
bool	is_reproduction(char *word)
{
	const char	*reproductions[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	size_t	index;

	index = 0;
	while (reproductions[index])
	{
		if (ft_strequal(word, reproductions[index]))
			return (true);
		index++;
	}
	return (false);
}



void	make_set_list(t_redirection_set **set, char **elements, size_t elements_num)
{
	t_redirection_set	*new;
	size_t				index;

	index = 0;
	while (index < elements_num)
	{
		new = ft_calloc(1, sizeof(t_redirection_set));
		if (!new)
			exit_fatal();
		new->word = ft_strdup(elements[index]); // 各要素の代入 (Substitution of each element)
		if (index == 0)
			new->type = NULL; // first, とかを enum で作っても良い。
		else
			new->type = get_redirection_type(elements[index - 1]);
		lstadd_back(set, new); // libft と名前が重複するため
		index += 2;
	}
}

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
void	exec_split(char **chunk_words)
{
	t_redirection_set	*set;
	t_fd				fds;
	size_t				strs_num;
	char				**elements;

	set_fds(&fds);
	set = NULL; // 返り値で作った方が綺麗な感じはする。まあ、動いてからでいいや。
	make_set_list(&set, elements, strs_num);
}

void	exec_no_pipe_chunk(char **piped_chunks)
{
	char	**chunk_words;

	chunk_words = space_and_tab_split(piped_chunks[0]);
	if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
		exec_split(chunk_words);
	else	
		fork_exec_commands(piped_chunks);
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