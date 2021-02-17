/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/17 15:46:32 by monoue           ###   ########.fr       */
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
	ft_free_split(argv);
	g_last_exit_status = 0;
}

static void	shape_arg(char **chunk_words, char ***argv, size_t *index,
																t_list *envp)
{
	char	**tmp;
	int		j;

	if (dollar_or_not(chunk_words[*index], '$'))
	{
		(*argv)[*index] = dollar(chunk_words[*index], envp, 0);
		if (g_space == true)
		{
			tmp = ft_split((*argv)[*index], ' ');
			j = 0;
			while (tmp[j])
			{
				free((*argv)[*index]);
				(*argv)[*index] = tmp[j];
				(*index)++;
				j++;
			}
			ft_free_split(tmp);
		}
	}
	else
		(*argv)[*index] = remove_escape(chunk_words[*index]);
}

static char	**set_command_argv(char **chunk_words, size_t args_num,
																t_list *envp)
{
	char	**argv;
	char	**tmp;
	size_t	index;
	int		j;

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
		shape_arg(chunk_words, &argv, &index, envp);
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
