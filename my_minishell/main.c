/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/01/28 12:54:45 by monoue           ###   ########.fr       */
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

char	*builtin_str[] = {
	"cd",
	"help",
	"exit",
};

// int	(*builtin_func[])(char **) = {
// 	&cd,
// 	&help,
// 	&lsh_exit
// };

int	num_builtins()
{
	return (sizeof(builtin_str) / sizeof(char *));
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


t_type	get_type(char *arg)
{
	if (!arg)
		return (TYPE_END);
	if (ft_strequal(arg, "|"))
		return (TYPE_PIPE);
	if (ft_strequal(arg, ";"))
		return (TYPE_BREAK);
	if (ft_strequal(arg, "<"))
		return (TYPE_READ);
	if (ft_strequal(arg, ">"))
		return (TYPE_WRITE);
	if (ft_strequal(arg, ">>"))
		return (TYPE_APPEND);
	return (ERROR);
}

size_t	count_chunk_members(char **argv)
{
	size_t	index;;

	index = 0;
	while (argv[index] && !ft_strequal(argv[index], "|") && !ft_strequal(argv[index], ";") && !ft_strequal(argv[index], ">") && !ft_strequal(argv[index], ">>"))
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

bool	is_type_read(t_chunk *chunk)
{
	if (!chunk)
		return (false);
	return (chunk->type == TYPE_READ);
}

bool	is_type_write(t_chunk *chunk)
{
	if (!chunk)
		return (false);
	return (chunk->type == TYPE_WRITE);
}

bool	is_type_append(t_chunk *chunk)
{
	if (!chunk)
		return (false);
	return (chunk->type == TYPE_APPEND);
}

#include <fcntl.h>

void	do_child(t_chunk *chunk)
{
	extern char	**environ;
	char		*fullpath_cmd;

	if (is_type_pipe(chunk) || is_type_write(chunk) || is_type_append(chunk))
	{
		if (dup2(chunk->fds[1], STDOUT_FILENO) == ERROR)
			exit_fatal();
		close(chunk->fds[0]); // どうせ、次のプロセスに引き継がれるのは、親プロセスだから…？
		close(chunk->fds[1]);
	}
	if (is_type_pipe(chunk->prev) || is_type_write(chunk->prev) || is_type_append(chunk->prev))
	{
		if (dup2(chunk->prev->fds[0], STDIN_FILENO) == ERROR) // 前のヤツの出口から標準入力に流れるようにしている。
			exit_fatal();
		// close(chunk->prev->fds[0]);
	}
	if (ft_strequal(chunk->argv[0], "help"))
		help();
	else if (ft_strequal(chunk->argv[0], "exit"))
		minishell_exit();
	else if (ft_strequal(chunk->argv[0], "pwd"))
		pwd(chunk);
	else if (ft_strequal(chunk->argv[0], "wc"))
		wc(fullpath_cmd, chunk, environ);
	else if (ft_strequal(chunk->argv[0], "echo"))
		echo(chunk);
	else if (ft_strequal(chunk->argv[0], "env"))
		env(environ);
	else if (ft_strequal(chunk->argv[0], "export"))
		export(chunk, environ);
	else if (is_type_write(chunk->prev))
	{
		char	*line;
		int fd = open(chunk->argv[0], O_CREAT | O_WRONLY, 0644);
		while (get_next_line(0, &line) > 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	else if (is_type_append(chunk->prev))
	{
		char	*line;
		int fd = open(chunk->argv[0], O_APPEND | O_WRONLY);
		while (get_next_line(0, &line) > 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	else
	{
		fullpath_cmd = ft_strjoin("/bin/", chunk->argv[0]);
		if (!fullpath_cmd)
			perror("");
		else if (execve(fullpath_cmd, chunk->argv, environ) == ERROR)
			perror("execve: ");
		SAFE_FREE(fullpath_cmd);
	}
	exit(EXIT_SUCCESS);
}

void	do_parent(t_chunk *chunk, pid_t child_pid, bool is_pipe_open)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (is_pipe_open)
	{
		close(chunk->fds[1]);
		if (!chunk->next || chunk->type == TYPE_BREAK)
			close(chunk->fds[0]); // このように、出力側を閉じないと動かない。なぜ閉じると動く？
	}
	if (is_type_pipe(chunk->prev) || is_type_write(chunk->prev) || is_type_append(chunk->prev))
		close(chunk->prev->fds[0]); // 前のを閉じることで、
}

void	exec_cmd(t_chunk *chunk)
{
	pid_t		pid;
	bool		is_pipe_open;

	is_pipe_open = false;
	if (is_type_pipe(chunk) || is_type_pipe(chunk->prev) || is_type_write(chunk) || is_type_write(chunk->prev) || is_type_append(chunk) || is_type_append(chunk->prev))
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
		// TODO: if (is_quoted_wrongly(line))
		argv = split_cmd_line(line);
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

int main(void)
{
	ft_putstr_err("Bienvenue dans notre Minishell ❤️\n");
	loop();
	return (EXIT_SUCCESS);
}
