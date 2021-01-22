/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/01/22 13:13:17 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MALLOC_ERR "memory allocation error\n"

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

int	cd(char **args);
int	help(char **args);
int	lsh_exit(char **args);

char	*builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int	(*builtin_func[])(char **) = {
	&cd,
	&help,
	&lsh_exit
};

int	num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
}

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir("/") == ERROR)
			perror("");
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			perror("");
	}
	return 1;
}

int	help(char **args)
{
	int	i;

	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in: \n");
	i = 0;	
	while (i < num_builtins())
	{
		printf(" %s\n", builtin_str[i]);
		i++;
	}
	return (1);
}

int	lsh_exit(char **args)
{
	return (0);
}

// int		launch(char **args)
// {
// 	extern char	**environ;
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == ERROR)
// 		perror("");
// 	else if (pid == 0) // 子プロセス
// 	{
// 		if (execve(args[0], args, environ) == ERROR)
// 			exit_err_msg("execvp failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		status = false;
// 		while (!WIFEXITED(status) && !WIFSIGNALED(status))
// 			waitpid(pid, &status, WUNTRACED); // 子プロセスが停止した場合にも復帰する。
// 	}
// 	return (1);
// }

// int		execute(char **args)
// {
// 	int	i;

// 	if (!args[0])
// 		return (1);
// 	i = 0;
// 	while (i < num_builtins())
// 	{
// 		if (ft_strequal(args[0], builtin_str[i]))
// 			return ((*builtin_func[i])(args));
// 		i++;
// 	}
// 	return (launch(args));
// }

t_chunk	*lstlast(t_chunk *chunk)
{
	if (!chunk)
		return (NULL);
	while (chunk->next)
		chunk = chunk->next;
	return (chunk);
}

void	lstadd_back(t_chunk **chunks, t_chunk *new)
{
	t_chunk	*tmp;

	if (!chunks || !new)
		return ;
	if (!(*chunks))
	{
		*chunks = new;
		return ;
	}
	tmp = lstlast(*chunks);
	tmp->next = new;
	new->prev = tmp;
}

t_type	get_type(char *arg)
{
	if (!arg)
		return (TYPE_END);
	if (ft_strequal(arg, "|"))
		return (TYPE_PIPE);
	if (ft_strequal(arg, ";"))
		return (TYPE_BREAK);
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
	new->size = count_chunk_members(argv); // count_chunk_members???
	// new->argv = malloc(sizeof(char *) * new->size + 1); // calloc 使っておけば、ft_free_split できる。
	// new->argv = malloc(sizeof(char *) * new->size + 1);
	new->argv = ft_calloc(new->size + 1, sizeof(char *));
	if (!new->argv)
		exit_fatal();
	index = 0;
	while (index < new->size)
	{
		new->argv[index] = ft_strdup(argv[index]); // 各要素の代入
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

void	do_child(t_chunk *chunk)
{
	extern char	**environ;

	if (is_type_pipe(chunk))
	{
		// その前に close しなくていいのか？
		if (dup2(chunk->fds[1], STDOUT_FILENO) == ERROR)
			exit_fatal();
	}
	if (is_type_pipe(chunk->prev))
	{
		if (dup2(chunk->prev->fds[0], STDIN_FILENO) == ERROR)
			exit_fatal();
	}
	if (execve(chunk->argv[0], chunk->argv, environ) == ERROR)
		perror("execve: ");
	exit(EXIT_SUCCESS);
}

void	do_parent(t_chunk *chunk, pid_t child_pid, bool is_pipe_open)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (is_pipe_open)
	{
		close(chunk->fds[1]); // ひとまず、このチャンクにて書き込むことはなくなるので閉じる。
		if (!chunk->next || chunk->type == TYPE_BREAK) // 次がない、もしくはここで区切れているなら
			close(chunk->fds[0]); // 読み込む必要もなくなるので閉じる。
	}
	if (is_type_pipe(chunk->prev)) // 前のチャンクにて読む必要もなくなる（？）ので閉じる。
		close(chunk->prev->fds[0]);
}

void	exec_cmd(t_chunk *chunk)
{
	pid_t		pid;
	bool		is_pipe_open;

	is_pipe_open = false;
	if (is_type_pipe(chunk) || is_type_pipe(chunk->prev))
	{
		is_pipe_open = true;
		if (pipe(chunk->fds) == ERROR)
			exit_fatal();
	}
	pid = fork();
	if (pid == ERROR)
		exit_fatal();
	if (pid == 0)
		do_child(chunk);
	else
		do_parent(chunk, pid, is_pipe_open);
}

void	exec_cmds(t_chunk *ptr)
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
			exec_cmd(tmp);
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
		index = 0;
		// TODO: ft_free_split に置き換えて試す。
		while (index < ptr->size)
		{
			free(ptr->argv[index]);
			index++;
		}
		free(ptr->argv);
		// ここまで
		free(ptr);
		ptr = tmp;
	}
	ptr = NULL;
}

void	loop(void)
{
	t_chunk	*chunk;
	t_chunk	*new;
	// ここまで追加
	size_t	index;

	char	*line;
	char	**argv;
	int		status;

	status = true;
	while (status)
	{
		ft_putstr("❯ ");
		if (get_next_line(STDIN_FILENO, &line) == ERROR)
			exit_err_msg(MALLOC_ERR);
		argv = ft_split(line, ' ');
		// if (ft_count_strs(args) == 0)
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
		exec_cmds(chunk);
		clear_leaks(chunk);

		// status = execute(args); 以下、この一行を、exam バージョンに変更中
		// ここから
		
		

		// ここまで
		SAFE_FREE(line);
		ft_free_split(argv);
	}
}

int main(int argc, char **argv, char **env)
{
	ft_putstr_err("❤️\n");
	loop();
	return (EXIT_SUCCESS);
}
