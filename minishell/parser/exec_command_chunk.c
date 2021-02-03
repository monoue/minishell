#include "../minishell.h"

static void	exec_reproduction(char **argv)
{
	if (ft_strequal(argv[0], "echo"))
		echo(argv);
	else if (ft_strequal(argv[0], "cd"))
		cd(argv);
}

static void	exec_command_argv(char **argv)
{
	extern char	**environ;
	char		*fullpath_cmd;

	if (is_reproduction(argv[0]))
		exec_reproduction(argv);
	else
	{
		if (ft_strequal(argv[0], "wc"))
			fullpath_cmd = ft_strjoin("/usr/bin/", argv[0]);
		// 後で綺麗に書き直す
		else
			fullpath_cmd = ft_strjoin("/bin/", argv[0]);
		if (!fullpath_cmd)
			perror("");
		else if (execve(fullpath_cmd, argv, environ) == ERROR)
			perror("execve: ");
		SAFE_FREE(fullpath_cmd);
		exit(EXIT_SUCCESS);
	}
}

static char	**set_command_argv(char **chunk_words, size_t args_num)
{
	char	**argv;
	size_t	index;

	argv = ft_calloc(args_num + 1, sizeof(char*));
	index = 0;
	while (index < args_num)
	{
		argv[index] = chunk_words[index];
		index++;
	}
	return (argv);
}

// static void	exec_command_chunk(char *command_chunk)
void	exec_command_chunk(char *command_chunk)
{
	t_fd	fds;
	size_t	args_num;
	char	**argv;
	char	**chunk_words;

	chunk_words = space_and_tab_split(command_chunk);
	set_fds(&fds);
	args_num = set_redirections_if(chunk_words, &fds);
	argv = set_command_argv(chunk_words, args_num);
	exec_command_argv(argv);
}

