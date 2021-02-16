#include "minishell.h"
#include "libft.h"

static void	exec_reproduction(char **argv, t_list *envp)
{
	if (ft_strequal(argv[0], "exit"))
		exit_minishell(argv);
	else if (ft_strequal(argv[0], "cd"))
		cd(argv, envp);
	else if (ft_strequal(argv[0], "pwd"))
		pwd(argv);
	else if (ft_strequal(argv[0], "echo"))
		echo(argv);
	else if (ft_strequal(argv[0], "env"))
		env(envp);
	else if (ft_strequal(argv[0], "export"))
		export(argv, envp);
	else if (ft_strequal(argv[0], "unset"))
		unset(argv, envp);
}

static void	exec_command_argv(char **argv, t_list *envp)
{
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp);
	else
		exec_path_command(argv, envp);
	g_last_exit_status = 0;
}

static char	**set_command_argv(char **chunk_words, size_t args_num,
																t_list *envp)
{
	char	**argv;
	size_t	index;

	argv = ft_calloc(args_num + 1, sizeof(char*));
	if (!argv)
		exit_err_msg(MALLOC_ERR);
	if (args_num < 2)
	{
		argv[0] = ft_strdup(chunk_words[0]);
		return (argv);
	}
	index = 0;
	while (index < args_num)
	{
		if (dollar_or_not(chunk_words[index], '$'))
		{
			argv[index] = dollar(chunk_words[index], envp);
			if (space == 1)
			{
				char **tmp;
				tmp = ft_split(argv[index], ' ');
				int j = 0;
				while (tmp[j])
				{
					free(argv[index]);
					argv[index] = tmp[j];
					index++;
					j++;
				}
			}
		}
		else
		{
			char *arg;
			arg = ft_strdup(chunk_words[index]);
			argv[index] = remove_escape(arg);
		}
		index++;
	}
	return (argv);
}

static void	reset_redirection_fds(t_fd fds)
{
	if (fds.input != STDIN_FILENO)
	{
		dup2(fds.input, STDIN_FILENO);
		close(fds.input);
	}
	if (fds.output > 2)
	{
		dup2(fds.output, STDOUT_FILENO);
		close(fds.output);
	}
}

void		exec_command_chunk(char *command_chunk, t_list *envp,
																bool pipe_child)
{
	t_fd	fds;
	size_t	args_num;
	char	**argv;
	char	**chunk_words;

	chunk_words = split_command_line(command_chunk);
	set_fds(&fds);
	args_num = process_redirections(chunk_words, &fds, envp);
	if (!is_redirection_str(chunk_words[0]))
	{
		argv = set_command_argv(chunk_words, args_num, envp);
		exec_command_argv(argv, envp);
	}
	ft_free_split(chunk_words);
	reset_redirection_fds(fds);
	if (pipe_child)
		exit(0);
}
