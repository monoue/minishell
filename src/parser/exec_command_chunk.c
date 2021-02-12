#include "minishell.h"
#include "libft.h"

static void	exec_reproduction(char **argv, t_list *envp)
{
	// const 

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

char	*get_path_str(t_list *envp)
{
	const char		*path_indicator = "PATH=";
	const size_t	len = ft_strlen(path_indicator);
	char			*env;

	while (envp)
	{
		env = (char*)envp->content;
		if (ft_strnequal(env, path_indicator, len))
			return (ft_strdup(&env[len]));
		envp = envp->next;
	}
	return (NULL);
}

void	exec_all_paths(char **paths, char **argv, t_list *envp)
{
	const char	*command = argv[0];
	char		*full_command_path;
	size_t		index;
	char		**environ;
	int			exec_ret;

	if (paths)
	{
		environ = turn_envp_into_strs(envp);
		index = 0;
		while (paths[index])	
		{
			full_command_path = ft_strjoin(paths[index], command);
			exec_ret = execve(full_command_path, argv, environ);
			SAFE_FREE(full_command_path);
			index++;
		}
	}
	errno = 0;
	execve(command, argv, environ);
}

char	**get_paths(char *path_str)
{
	char	**paths_without_slash;
	char	**complete_paths;
	size_t	paths_num;
	size_t	index;

	if (!path_str)
		return (NULL);
	paths_without_slash = ft_split_skipping_quotes(path_str, ':');
	if (!paths_without_slash)
		return (NULL);
	paths_num = ft_count_strs((const char**)paths_without_slash);
	complete_paths = malloc((paths_num + 1) * sizeof(char *));
	if (!complete_paths)
		return (NULL);
	index = 0;
	while (index < paths_num)
	{
		complete_paths[index] = ft_strjoin(paths_without_slash[index], "/");
		index++;
	}
	complete_paths[index] = NULL;
	ft_free_split(paths_without_slash);
	return (complete_paths);
}

void		handle_exec_error(const char *command)
{
	if (errno == ENOENT)
		exit_bash_err_msg(command, strerror(ENOENT), 127);
	if (errno == EACCES)
		exit_bash_err_msg(command, strerror(EISDIR), 127);
	if (errno == ENOTDIR)
		exit_bash_err_msg(command, strerror(ENOTDIR), 126);
	exit_bash_err_msg(command, NO_COMMANDS_ERR, 127);
}

void		exec_path_command(char **argv, t_list *envp)
{
	char		**paths;
	char		*path_str;

	path_str = get_path_str(envp);
	paths = get_paths(path_str);
	if (path_str)
		SAFE_FREE(path_str);
	exec_all_paths(paths, argv, envp);
	handle_exec_error(argv[0]);
}

static void	exec_command_argv(char **argv, t_list *envp)
{
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp);
	else
		exec_path_command(argv, envp);
	g_last_exit_status = 0;
}

// static char	**set_command_argv(char **chunk_words, size_t args_num, t_list *envp)
// {
// 	char	**argv;
// 	size_t	index;

// 	argv = ft_calloc(args_num + 1, sizeof(char*));
// 	index = 0;
// 	while (index < args_num)
// 	{
// 		if (chunk_words[1] != NULL)
// 		{
// 			if (is_env(chunk_words[index], '$'))
// 			// これだと、元の chunk_words[index] がフリーできなくなる
// 				chunk_words[index] = dollar(chunk_words[index], envp);
// 		}
// 		argv[index] = chunk_words[index];
// 		index++;
// 	}
// 	return (argv);
// }

static char	**set_command_argv(char **chunk_words, size_t args_num, t_list *envp)
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
			argv[index] = dollar(chunk_words[index], envp);
		else
			argv[index] = ft_strdup(chunk_words[index]);
		index++;
	}
	return (argv);
}

void	reset_redirection_fds(t_fd fds)
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

void	exec_command_chunk(char *command_chunk, t_list *envp)
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
	reset_redirection_fds(fds);
}
