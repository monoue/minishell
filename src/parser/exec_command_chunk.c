/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 07:00:16 by monoue           ###   ########.fr       */
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

// static void	shape_arg(char *chunk_words, char ***argv, size_t *index,
// 																t_list *envp)
// {
// 	// if (dollar_or_not(chunk_words, '$'))
// 	// 	(*argv)[*index] = dollar(chunk_words, envp);
// 	// else if (chunk_words[0] != '\'')
// 	// 	(*argv)[*index] = remove_escape(chunk_words);
// 	else
// 		(*argv)[*index] = ft_strdup(chunk_words);
// 	DS((*argv)[*index]);
// }

static char	**set_command_argv(char **chunk_words, size_t args_num,
																t_list *envp)
{
	char	**argv;
	char	**tmp;
	size_t	index;
	int		j;

	g_space = 0;
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
		argv[index] = ft_strdup(chunk_words[index]);
		if (argv[index][0] == '\"' && argv[index][1] == ' ' && argv[index][2] != '\'')
		{
			tmp = ft_split(argv[index], ' ');
			j = 0;
			while (tmp[j])
			{
				free(argv[index]);
				argv[index] = tmp[j];
				index++;
				j++;
			}
			// ft_free_split(tmp);
		}
		if (ft_strcmp(argv[index], "\"\\\"") != 0)
			argv[index] = remove_quotes(argv[index]);
		index++;
	}
	return (argv);
}

// static char	**set_command_argv(char **chunk_words, size_t args_num,
// 																t_list *envp)
// {
// 	char	**argv;
// 	char	**tmp;
// 	char	*str;
// 	char	*arg_tmp;
// 	size_t	index;
// 	int		j;

// 	g_space = 0;
// 	argv = malloc(sizeof(*argv) * MAX_INPUT);
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
// 		arg_tmp = ft_strdup(chunk_words[index]);
// 		// if (arg_tmp[0] == '\"' && arg_tmp[1] == ' ' && arg_tmp[2] != '\'')
// 		// {
// 		// 	tmp = ft_split(arg_tmp, ' ');
// 		// 	j = 0;
// 		// 	while (tmp[j])
// 		// 	{
// 		// 		SAFE_FREE(arg_tmp);
// 		// 		argv[index] = tmp[j];
// 		// 		index++;
// 		// 		j++;
// 		// 	}
// 		// 	// ft_free_split(tmp);
// 		// }
// 		if (g_flag_dont == 0)
// 			str = remove_quotes(arg_tmp);
// 		argv[index] = strdup(str);
// 		index++;
// 		SAFE_FREE(arg_tmp);
// 		SAFE_FREE(str);
// 	}
// 	return (argv);
// }

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

	// chunk_words = split_command_line(command_chunk);
	chunk_words = split_command_line(command_chunk, envp);
	set_fds(&fds);
	// TODO: リダイレクション部分以降も execve の引数としてとれるようにする
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
