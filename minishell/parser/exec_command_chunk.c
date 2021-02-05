#include "../minishell.h"

static void	exec_reproduction(char **argv, t_list *envp)
{
	if (ft_strequal(argv[0], "help"))
		help();
	else if (ft_strequal(argv[0], "exit"))
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
	char		*fullpath_cmd;
	char		**environ;

	// if (argv[1] != NULL)
	// 	if (dollar_or_not(argv[1], '$'))
	// 		argv[1] = dollar(argv, envp);
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp);
	else
	{	environ = struct_to_array(envp);
		if (ft_strequal(argv[0], "wc") || ft_strequal(argv[0], "touch"))
			fullpath_cmd = ft_strjoin("/usr/bin/", argv[0]);
		// 後で綺麗に書き直す
		else
			fullpath_cmd = ft_strjoin("/bin/", argv[0]);
		if (!fullpath_cmd)
			ft_putendl_fd(strerror(errno), 1);

		else if (execve(fullpath_cmd, argv, environ) == ERROR) //ici changer
		{
			ft_putstr_fd("execve: ", 1);
			ft_putendl_fd(strerror(errno), 1);
		}
		SAFE_FREE(fullpath_cmd);
		exit(EXIT_SUCCESS);
	}
}

static char	**set_command_argv(char **chunk_words, size_t args_num, t_list *envp)
{
	char	**argv;
	size_t	index;

	argv = ft_calloc(args_num + 1, sizeof(char*));
	index = 0;
	while (index < args_num)
	{
		if (chunk_words[1] != NULL)
		{
			if (dollar_or_not(chunk_words[index], '$'))
				chunk_words[index] = dollar(chunk_words[index], envp);
		}
		argv[index] = chunk_words[index];
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

	chunk_words = dollar_split(command_chunk);
	set_fds(&fds);
	args_num = process_redirections(chunk_words, &fds);
	argv = set_command_argv(chunk_words, args_num, envp);
	exec_command_argv(argv, envp);
}
