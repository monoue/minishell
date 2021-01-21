#include "microshell.h"

void	ft_putstr_err(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	exit_fatal(void)
{
	ft_putstr_err("error: fatal\n");
	exit(EXIT_FAILURE);
}

void	ft_lstadd_back(t_chunk **chunks, t_chunk *new)
{
	t_chunk	*tmp;

	if (*chunks == NULL)
	{
		*chunks = new;
		return ;
	}
	tmp = *chunks;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}

int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0)
		i++;
	return (i);
}


int	get_last_arg_type(char *arg)
{
	if (arg == NULL)
		return (TYPE_END);
	if (strcmp(arg, "|") == 0)
		return (TYPE_PIPE);
	if (strcmp(arg, ";") == 0)
		return (TYPE_BREAK);
	return (0);
}

int	add_parsed_info_back(t_chunk **lst, char **argv)
{
	int		size;
	t_chunk	*new;

	new = malloc(sizeof(t_chunk));
	if (new == NULL)
		exit_fatal();
	size = count_args(argv);
	new->argv = malloc(sizeof(char *) * (size + 1));
	if (new->argv == NULL)
		exit_fatal();
	new->size = size;
	new->next = NULL;
	new->previous = NULL;
	new->argv[size] = NULL;
	int	index;

	index = 0;
	while (index < size)
	{
		new->argv[index] = ft_strdup(argv[index]);
		if (new->argv[index] == NULL)
			exit(EXIT_FAILURE);
		index++;
	}
	new->type = get_last_arg_type(argv[new->size]); // 区切れの最後の要素
	ft_lstadd_back(lst, new); // 本家とは、「空なら作る」点が異なる。-> 本家のを使って調整すべき…？
	return (new->size);
}

bool	is_type_pipe(t_chunk *chunk)
{
	if (!chunk)
		return (false);
	return (chunk->type == TYPE_PIPE);
}

void	exit_execve(char *str)
{
	ft_putstr_err("error: cannnot execute ");
	ft_putstr_err(str);
	ft_putstr_err("\n");
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_chunk *chunk, char **env)
{
	pid_t	pid;
	int		status;
	bool	is_pipe_open;

	is_pipe_open = false;
	if (is_type_pipe(chunk) || is_type_pipe(chunk->previous))
	{
		is_pipe_open = true;
		if (pipe(chunk->pipefds) == ERROR)
			exit_fatal();
	}
	pid = fork();
	if (pid == ERROR)
		exit_fatal();
	if (pid == HAS_NO_CHILD) // child
	{
		// if (tmp->type == TYPE_PIPE && dup2(temp->pipefds[1], STDOUT) < 0)
		if (is_type_pipe(chunk))
		{
			if (dup2(chunk->pipefds[WRITE_END], STDOUT_FILENO) == ERROR)  // 標準出力への出力を、入力として受け取れるように設定しているっぽい
				exit_fatal();
		}
		// if (tmp->previous && tmp->previous->type == TYPE_PIPE)
		if (is_type_pipe(chunk->previous))
		{
			if (dup2(chunk->previous->pipefds[READ_END], STDIN_FILENO) == ERROR) // 一つ前のものへの入力を、標準入力にしているっぽい 
				exit_fatal();
		}
		if ((execve(chunk->argv[0], chunk->argv, env)) == ERROR)
			exit_execve(chunk->argv[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0); // 子プロセスを待つ。第三引数の 0 は特に気にしなくて良い。
		if (is_pipe_open)
		{
			close(chunk->pipefds[WRITE_END]);
			if (!chunk->next || chunk->type == TYPE_BREAK)
				close(chunk->pipefds[READ_END]);
		}
		if (is_type_pipe(chunk->previous))
			close(chunk->previous->pipefds[READ_END]);
	}
}

void	exec_cmds(t_chunk *ptr, char **env)
{
	t_chunk	*tmp;

	tmp = ptr;
	while (tmp)
	{
		if (strcmp("cd", tmp->argv[0]) == 0)
		{
			if (tmp->size == 1)
				ft_putstr_err("error: cd: bad arguments\n");
			else if (chdir(tmp->argv[1]) == ERROR)
			{
				ft_putstr_err("error: cd: cannot change directory to ");
				ft_putstr_err(tmp->argv[1]);
				ft_putstr_err("\n");
			}
		}
		else
			exec_cmd(tmp, env);
		tmp = tmp->next;
	}
}

void	clear_leaks(t_chunk *ptr)
{
	t_chunk	*tmp;
	int		i;

	while (ptr)
	{
		tmp = ptr->next;
		i = 0;
		while (i < ptr->size)
		{
			free(ptr->argv[i]);
			i++;
		}
		free(ptr->argv);
		free(ptr);
		ptr = tmp;
	}
	ptr = NULL;
}

int main(int argc, char *argv[], char **env)
{
	t_chunk	*chunk;
	int		i;

	if (argc <= 1)
		return (EXIT_SUCCESS);
	i = 1;
	chunk = NULL;
	while (argv[i])
	{
		if (strcmp(argv[i], ";") == 0)
		{
			i++;
			continue;
		}
		i += add_parsed_info_back(&chunk, &argv[i]); // どうやら、argv を、区切られた塊ごとの文字列の配列に分けているのでは…？
		if (argv[i] == NULL)
			break;
		i++;
	}
	if (chunk)
		exec_cmds(chunk, env);
	clear_leaks(chunk);
	return (EXIT_SUCCESS);
}