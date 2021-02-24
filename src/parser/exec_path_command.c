/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:24:05 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 13:18:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	exec_all_paths(char **paths, char **argv, t_list *envp)
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
}

static void	handle_exec_error(const char *command)
{
	if (errno == ENOENT)
		exit_bash_err_msg(command, strerror(ENOENT), 127);
	if (errno == EACCES)
		exit_bash_err_msg(command, strerror(EISDIR), 126);
	if (errno == ENOTDIR)
		exit_bash_err_msg(command, strerror(ENOTDIR), 126);
	exit_bash_err_msg(command, NO_COMMANDS_ERR, 127);
}

static char	*get_path_str(t_list *envp)
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

static char	**get_paths(char *path_str)
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

static void	exec_absolute_path(char **argv, t_list *envp)
{
	const char	*command = argv[0];
	char		**environ;

	environ = turn_envp_into_strs(envp);
	errno = 0;
	execve(command, argv, environ);
}

void		exec_path_command(char **argv, t_list *envp)
{
	char		**paths;
	char		*path_str;

	if (ft_strchr(argv[0], '/'))
	{
		exec_absolute_path(argv, envp);
		handle_exec_error(argv[0]);
	}
	else
	{
		path_str = get_path_str(envp);
		paths = get_paths(path_str);
		if (path_str)
			SAFE_FREE(path_str);
		exec_all_paths(paths, argv, envp);
		exit_bash_err_msg(argv[0], NO_COMMANDS_ERR, 127);
	}
}
