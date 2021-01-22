# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h> // EXIT_SUCCESS / FAILURE
# include <stdbool.h>

# define ERR_MSG		"error: "
# define FATAL_ERR_MSG	ERR_MSG"fatal\n"

# define ERROR		-1
# define SUCCESS	0

typedef			enum
{
	TYPE_END,
	TYPE_PIPE,
	TYPE_BREAK,

	TYPES_NUM
}				t_type;

typedef struct	s_chunk
{
	char			**argv;
	size_t			size;
	t_type			type;
	int				fds[2];

	struct s_chunk	*prev;
	struct s_chunk	*next;
}				t_chunk;

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	index;

	index = 0;
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

char	*ft_strdup(char const *str)
{
	size_t	count;
	char	*ret_s;

	count = ft_strlen(str);
	ret_s = malloc(sizeof(char) * (count + 1));
	if (!ret_s)
		return (NULL);
	return (ft_strcpy(ret_s, str));
}

void	ft_putstr_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	exit_fatal(void)
{
	ft_putstr_err(FATAL_ERR_MSG);
	exit(EXIT_FAILURE);
}

bool	ft_strequal(const char *s1, const char *s2)
{
	return (strcmp(s1, s2) == 0);
}






size_t	count_chunk_members(char **argv)
{
	size_t	index;;

	index = 0;
	while (argv[index] && !ft_strequal(argv[index], "|") && !ft_strequal(argv[index], ";"))
		index++;
	return (index);
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

// int	add_parsed_info_back(t_chunk **chunks, char **argv)
// void	chunk_add_back(t_chunk **chunks, char **argv)
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
	new->argv = malloc(sizeof(char *) * new->size + 1);
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

int	main(int argc, char *argv[])
{
	t_chunk	*chunk;
	t_chunk	*new;
	int		i;

	if (argc <= 1)	
		return (EXIT_SUCCESS);
	i = 1;
	chunk = NULL; // ひとまず初期化
	while (argv[i])
	{
		if (ft_strequal(argv[i], ";")) 
		{
			i++;
			continue ;
		}
		new = chunk_add_back(&chunk, &argv[i]);
		if (new->type == TYPE_END)
			break ;
		i += (new->size + 1);
	}
	if (!chunk)
		return (EXIT_SUCCESS);
	exec_cmds(chunk);
	clear_leaks(chunk);
}