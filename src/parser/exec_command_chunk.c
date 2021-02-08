#include "../minishell.h"

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

size_t		exec_all_paths(char **paths, char **argv, t_list *envp)
{
	char	*full_command_path;
	size_t	index;
	char	**environ;
	int		exec_ret;

	if (!paths || !argv || !envp)
		return (0);
	index = 0;
	environ = turn_envp_into_strs(envp);
	while (paths[index])	
	{
		full_command_path = ft_strjoin(paths[index], argv[0]);
		exec_ret = execve(full_command_path, argv, environ);
		SAFE_FREE(full_command_path);
		if (exec_ret != ERROR)
			break ;
		index++;
	}
	return (index);
}

char	**get_paths(char *path_str)
{
	char	**paths_without_slash;
	char	**complete_paths;
	size_t	paths_num;
	size_t	index;

	if (!path_str)
		return (NULL);
	paths_without_slash = ft_split(path_str, ':');
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

void		exec_path_command(char **argv, t_list *envp)
{
	char	**paths;
	char	*path_str;
	size_t	try_count;

	path_str = get_path_str(envp);
	if (!path_str)
		exit_bash_err_msg(argv[0], strerror(2));
	paths = get_paths(path_str);
	if (path_str)
		SAFE_FREE(path_str);
	try_count = exec_all_paths(paths, argv, envp);
	if (try_count == ft_count_strs((const char**)paths))
	{
		ft_free_split(paths);
		exit_bash_err_msg(argv[0], "command not found");
	}
	exit(EXIT_SUCCESS);
}



static void	exec_command_argv(char **argv, t_list *envp)
{
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp);
	else
		exec_path_command(argv, envp);
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
// 			if (dollar_or_not(chunk_words[index], '$'))
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


void	exec_command_chunk(char *command_chunk, t_list *envp)
{
	t_fd	fds;
	size_t	args_num;
	char	**argv;
	char	**chunk_words;

	chunk_words = split_command_line(command_chunk);
	set_fds(&fds);
	args_num = process_redirections(chunk_words, &fds);
	argv = set_command_argv(chunk_words, args_num, envp);
	exec_command_argv(argv, envp);
}
