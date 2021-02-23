/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 14:42:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	exec_command_argv(char **argv, t_list *envp)
{
	if (is_reproduction(argv[0]))
		exec_reproduction(argv, envp);
	else
		exec_path_command(argv, envp);
	// ft_free_split(argv);
}

// static char	**set_command_argv(char **chunk_words, size_t args_num,
// 																t_list *envp)
// {
// 	char	**argv;
// 	char	**tmp;
// 	size_t	index;
// 	int		j;

// 	g_space = 0;
// 	argv = ft_calloc(args_num + 1, sizeof(char*));
// 	if (!argv)
// 		exit_err_msg(MALLOC_ERR);
// 	if (args_num < 2)
// 	{
// 		argv[0] = ft_strdup(chunk_words[0]);
// 		return (argv);
// 	}
// 	index = 0;
// 	while (index < args_num)
// 	{
// 		g_global = 0;
// 		if (dollar_or_not(chunk_words[index], '$'))
// 			argv[index] = dollar(chunk_words[index], envp);
// 		else
// 			argv[index] = ft_strdup(chunk_words[index]);
// 		if (g_global == 0)
// 			argv[index] = remove_quotes(argv[index]);
// 		if (g_global == 0 && argv[index][0] != '\"')
// 			argv[index] = remove_escape(argv[index]);
// 		else if (g_global == 0 && argv[index][0] != '\"'
// 				&& argv[index][0] != '\'')
// 			argv[index] = remove_escape_dq(argv[index]);
// 		if (argv[index][0] == '\"' && argv[index][1] == ' '
// 				&& argv[index][2] != '\'')
// 		{
// 			tmp = ft_split(argv[index], ' ');
// 			j = 0;
// 			while (tmp[j])
// 			{
// 				// free(argv[index]);
// 				argv[index] = tmp[j];
// 				index++;
// 				j++;
// 			}
// 			// ft_free_split(tmp);
// 		}
// 		index++;
// 	}
// 	return (argv);
// }

static char	**set_command_argv(char **argv1, t_list *envp)
{
	const size_t	args_num = ft_count_strs((const char **)argv1);
	char	**argv2;
	char	**tmp;
	size_t	index;
	int		j;

	g_space = 0;
	argv2 = ft_calloc(args_num + 1, sizeof(char *));
	if (!argv2)
		exit_err_msg(MALLOC_ERR);
	if (args_num < 2)
	{
		argv2[0] = ft_strdup(argv1[0]);
		return (argv2);
	}
	index = 0;
	while (index < args_num)
	{
		argv2[index] = ft_strdup(argv1[index]);
		if (argv2[index][0] == '\"' && argv2[index][1] == ' ' && argv2[index][2] != '\'')
		{
			tmp = ft_split(argv2[index], ' ');
			j = 0;
			while (tmp[j])
			{
				free(argv2[index]);
				argv2[index] = tmp[j];
				index++;
				j++;
			}
			// ft_free_split(tmp);
		}
		if (ft_strcmp(argv2[index], "\"\\\"") != 0)
			argv2[index] = remove_quotes(argv2[index]);
		index++;
	}
	return (argv2);
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

// void		exec_command_chunk(char *command_chunk, t_list *envp,
// 																bool pipe_child)
// {
// 	t_fd	fds;
// 	size_t	args_num;
// 	char	**argv;
// 	char	**chunk_words;

// 	chunk_words = split_command_line(command_chunk, envp);
// 	set_fds(&fds);
// 	args_num = process_redirections(chunk_words, &fds, envp);
// 	if (!is_redirection_str(chunk_words[0]))
// 	{
// 		argv = set_command_argv(chunk_words, args_num, envp);
// 		exec_command_argv(argv, envp);
// 	}
// 	ft_free_split(chunk_words);
// 	reset_redirection_fds(fds);
// 	if (pipe_child)
// 		exit(0);
// }

void		exec_command_chunk(char *command_chunk, t_list *envp,
																bool pipe_child)
{
	t_fd	fds;
	size_t	args_num;
	char	**argv1;
	char	**argv2;
	char	**chunk_words;

	// chunk_words = split_command_line(command_chunk);
	chunk_words = split_command_line(command_chunk, envp);
	set_fds(&fds);
	// TODO: リダイレクション部分以降も execve の引数としてとれるようにする
	// args_num = process_redirections(chunk_words, &fds, envp);
	// process は process で１つ、他に extract argv みたいな関数を作るのが良い。
	process_redirections(chunk_words, &fds, envp);
	argv1 = extract_argv(chunk_words);
	ft_free_split(chunk_words);

	if (!is_redirection_str(argv1[0]))
	{
		// argv2 = set_command_argv(chunk_words, args_num, envp);
		// argv2 = set_command_argv(argv1, args_num, envp);
		argv2 = set_command_argv(argv1, envp);
		exec_command_argv(argv2, envp);
	}
	ft_free_split(argv1);
	ft_free_split(argv2);
	reset_redirection_fds(fds);
	if (pipe_child)
		exit(0);
}
