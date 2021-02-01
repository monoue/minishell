/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/01 16:50:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fatal(void)
{
	ft_putstr_err(FATAL_ERR_MSG);
	exit(EXIT_FAILURE);
}

void	exit_err_msg(char *err_msg)
{
	ft_putstr_err(err_msg);
	exit(EXIT_FAILURE);
}

typedef struct	s_redirection_combination {
	char	*symbol;
	t_type	type;
}				t_redirection_combination;

t_type	get_type(char *element)
{
	const t_redirection_combination redirection_sets[] = {
		{">", TYPE_OUTPUT},
		{">>", TYPE_APPEND},
		{">", TYPE_INPUT},
		{NULL, TYPES_NUM}
	};
	size_t					index;

	index = 0;
	while (index < TYPES_NUM)
	{
		if (ft_strequal(element, redirection_sets[index].symbol))
			return (redirection_sets[index].type);
		index++;
	}
	return (ERROR);
}

size_t	count_chunk_members(char **argv)
{
	size_t	index;;

	index = 0;
	while (argv[index] && !ft_strequal(argv[index], "|") && !ft_strequal(argv[index], ";"))
		index++;
	return (index);
}

t_chunk	*chunk_add_back(t_chunk **chunks, char **argv)
{
	t_chunk	*new;
	size_t	index;

	new = malloc(sizeof(t_chunk));
	if (!new)
		exit_fatal();
	// size = ft_count_strs(argv);
	new->size = count_chunk_members(argv); // count size of the command
	// new->argv = malloc(sizeof(char *) * new->size + 1); // calloc 使っておけば、ft_free_split できる。
	// new->argv = malloc(sizeof(char *) * new->size + 1);
	new->argv = ft_calloc(new->size + 1, sizeof(char *));
	if (!new->argv)
		exit_fatal();
	index = 0;
	while (index < new->size)
	{
		new->argv[index] = ft_strdup(argv[index]); // 各要素の代入 (Substitution of each element)
		if (!new->argv[index])
			exit_fatal();
		index++;
	}
	new->type = get_type(argv[new->size]);
	new->next = NULL;
	new->prev = NULL;	
	new->argv[new->size] = NULL;
	lstadd_back(chunks, new); // libft と名前が重複するため
	return (new);
}

bool	is_type_pipe(t_chunk *chunk)
{
	if (!chunk)
		return (false);
	return (chunk->type == TYPE_PIPE);
}

// void	do_child(t_chunk *chunk, t_list *envp)
// {
// 	extern char	**environ;
// 	char		*fullpath_cmd;

// 	if (is_type_pipe(chunk))
// 	{
// 		// その前に close しなくていいのか？
// 		// if (dup2(chunk->fds[1], STDOUT_FILENO) == ERROR) // この chunk からの出力を、標準出力にしている。
// 		// if (dup2(chunk->fds[1], STDOUT_FILENO) == ERROR) // 標準出力されたものは、このパイプに入ってくるようになっている。
// 		if (dup2(chunk->fds[1], STDOUT_FILENO) == ERROR) // 標準出力されたものがもしあったならば、このパイプが吸収するようにした。初回は関係ない。
// 			exit_fatal();									// ls | wc で言えば、wc の受け取り側
// 	}
// 	if (is_type_pipe(chunk->prev))
// 	{
// 		if (dup2(chunk->prev->fds[0], STDIN_FILENO) == ERROR) // 前の chunk で出されたものが、標準入力として解釈されるようになった。
// 			exit_fatal();										// ls | wc で言えば、ls の出すもの
// 	}
// 	if (ft_strequal(chunk->argv[0], "help"))
// 		help();
// 	else
// 	{
// 		fullpath_cmd = ft_strjoin("/bin/", chunk->argv[0]);
// 		if (!fullpath_cmd)
// 			perror("");
// 		else if (execve(fullpath_cmd, chunk->argv, environ) == ERROR)
// 			perror("execve: ");
// 		SAFE_FREE(fullpath_cmd);
// 	}
// 	exit(EXIT_SUCCESS);
// }

// void	do_parent(t_chunk *chunk, pid_t child_pid, bool is_pipe_open)
// {
// 	int	status;

// 	waitpid(child_pid, &status, 0);	// 閉じて初めて流れる
// 	if (is_pipe_open)
// 	{
// 		close(chunk->fds[1]); // ひとまず、このチャンクにて書き込むことはなくなるので閉じる。
// 		if (!chunk->next || chunk->type == TYPE_BREAK) // 次がない、もしくはここで区切れているなら
// 			close(chunk->fds[0]); // 読み込む必要もなくなるので閉じる。
// 	}
// 	if (is_type_pipe(chunk->prev)) // 前のチャンクにて読む必要もなくなる（？）ので閉じる。
// 		close(chunk->prev->fds[0]);
// }

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
// 	t_chunk	*tmp;

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

void	exec_cmd(t_chunk *chunk, t_list *envp)
{
	pid_t		pid;
	bool		is_pipe_open;
	int			flag;

	is_pipe_open = false;
	if (is_type_pipe(chunk) || is_type_pipe(chunk->prev))
	{
		is_pipe_open = true;
		if (pipe(chunk->fds) == ERROR)
			exit_fatal();
	}
	flag = pipe_or_not_pipe(chunk);//ここはPIPEあるかない、または builtinsではあるかないを確認して、FLAG＝０場合はコマンドを移動して、FLAG=１場合はFORKに行く
	if (flag == 0) 
		no_pipe(chunk, envp);//builtins
	else
	{
		pid = fork();
		if (pid == ERROR)
			exit_fatal();
		if (pid == 0)
			do_child(chunk, envp);
		else
			do_parent(chunk, pid, is_pipe_open);
	}
	flag = 0;
}

void	exec_cmds(t_chunk *ptr, t_list *envp)
{
	t_chunk	*tmp;

	tmp = ptr;
	while (tmp)
	{
		if (ft_strequal("cd", tmp->argv[0]))
		{
			if (tmp->size == 1)
				chdir("~");
			else if (chdir(tmp->argv[1]) == ERROR)
			{
				perror("cd: "); // 本物と一致しているかチェック
			}
		}
		else
			exec_cmd(tmp, envp);
		tmp = tmp->next;	
	}
}
void	clear_leaks(t_chunk *ptr)
{
	t_chunk	*tmp;
	size_t	index;

	while (ptr)
	{
		tmp = ptr->next;
		// index = 0;
		// TODO: ft_free_split に置き換えて試す。
		ft_free_split(ptr->argv);
		// while (index < ptr->size)
		// {
		// 	free(ptr->argv[index]);
		// 	index++;
		// }
		// free(ptr->argv);
		// ここまで
		SAFE_FREE(ptr);
		ptr = tmp;
	}
	ptr = NULL;
}


void	process_cmd_line(void)
{
	// t_chunk		*chunk;
	// t_chunk		*new;
	t_list		*envp;
	t_list		*tmp;
	// ここまで追加
	size_t		index;
	extern char **environ;
	char		*line;
	char		**argv;
	int			status;

	//環境変数のリスト構造体を作る
	envp = ft_lstnew(*environ);
    environ++;
    while (*environ)
    {
        tmp = ft_lstnew(*environ);
        ft_lstadd_back(&envp, tmp);
        environ++;
    }
	status = true;
	while (status)
	{
		ft_putstr("❯ ");
		if (get_next_line(STDIN_FILENO, &line) == ERROR)
			exit_err_msg(MALLOC_ERR);
		if (is_quoted_wrongly(line))
			exit(EXIT_FAILURE);
		argv = split_cmd_line(line);
		if (!ft_count_strs((const char**)argv))
			continue ;
		index = 0;
		chunk = NULL;
		while (argv[index])
		{
			if (ft_strequal(argv[index], ";"))
			{
				index++;
				continue ;
			}
			new = chunk_add_back(&chunk, &argv[index]);
			if (new->type == TYPE_END)
				break ;
			index += (new->size + 1);
		}
		if (!chunk)
			return ;
		exec_cmds(chunk, envp);
		clear_leaks(chunk);


		// status = execute(args); 以下、この一行を、exam バージョンに変更中
		// ここから
		
		

		// ここまで
		SAFE_FREE(line);
		ft_free_split(argv);
	}
}
typedef enum	e_redirection {
	REDIRECT_INPUT,
	REDIRECT_OVERRIDE,
	REDIRECT_APPEND,
	REDIRECT_NUM,
}				t_redirection;

typedef struct	s_fd {
	int	input;
	int	output;
}				t_fd;

void	set_fds(t_fd *fds)
{
	fds->input = STDIN_FILENO;
	fds->output = STDOUT_FILENO;
}

// void	skip_to_next_quote(char *p, char quote, size_t *index)
// {
// 	(*index)++;
// 	while (p[*index] != quote)	
// 		(*index)++;
// }

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
			new->type = get_type(elements[index - 1]);
		lstadd_back(set, new); // libft と名前が重複するため
		index += 2;
	}
}

void	exec_command_chunk(char *command_chunk)
{
	t_redirection_set	*set;
	t_fd				fds;
	size_t				index;
	size_t				strs_num;
	char				**elements;

	elements = split_cmd_line(command_chunk);
	strs_num = ft_count_strs((const char**)elements);
	if (!strs_num)
		return ;
	set_fds(&fds);
	set = NULL; // 返り値で作った方が綺麗な感じはする。まあ、動いてからでいいや。
	make_set_list(&set, elements, strs_num);
}

void	process_one_command(char *command)
{
	char	**piped_chunks;
	size_t	chunks_num;
	char	**chunk_words;

	piped_chunks = ft_split(command, '|');
	// エラー処理
	chunks_num = ft_count_strs(piped_chunks);
	if (chunks_num == 1)
	{
		chunk_words = space_n_tab_split(piped_chunks[0]);
		// エラー処理
		if (is_reproduction(chunk_words[0])) // 自作コマンドであるなら
			// それぞれ、exit のナンバーを後ほど受け取る
			exec_command_chunk(piped_chunks[0]);
		else	
			fork_exec_commands(piped_chunks);
	}
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

void	process_cmd_line(void)
{
	char	*line;

	ft_putstr(PROMPT);
	if (get_next_line(STDIN_FILENO, &line) == ERROR)
		exit_err_msg(MALLOC_ERR);
	if (is_invalid_syntax(line))
	{
		SAFE_FREE(line);
		exit(EXIT_FAILURE);
	}
	// 環境変数をここで整える
	// コメントもここで削る
	exec_one_line(line);
}

int main(void)
{
	ft_putstr_err("Bienvenue dans notre Minishell❤️\n");
	while (1)
	{
		// signal 系処理
		process_cmd_line();
	}
	return (EXIT_SUCCESS);
}
