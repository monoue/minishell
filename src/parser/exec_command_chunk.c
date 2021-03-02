/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 13:26:33 by sperrin          ###   ########.fr       */
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
}

void		fill_argv_with_replaced_env(char *arg, char **argv2,
								size_t *i2, t_list *envp)
{
	char	*dollar_applied;
	char	**tmp;
	size_t	index;

	dollar_applied = dollar(arg, envp);
	if (!dollar_applied)
		return ;
	if (g_flag_escape_db || !g_flag_dont)
	{
		argv2[*i2] = ft_strdup_free(dollar_applied);
		(*i2)++;
		return ;
	}
	if ((tmp = ft_split(dollar_applied, ' ')))
	{
		index = 0;
		while (tmp[index])
		{
			argv2[*i2] = ft_strdup_free(tmp[index]);
			(*i2)++;
			index++;
		}
		SAFE_FREE(tmp);
	}
	SAFE_FREE(dollar_applied);
}

char		**set_command_argv(char **argv1, t_list *envp)
{
	const size_t	arg_num = ft_count_strs((const char **)argv1);
	char			**argv2;
	size_t			i1;
	size_t			i2;

	g_space = false;
	if (!(argv2 = malloc(sizeof(char *) * MAX_INPUT)))
		exit_err_msg(MALLOC_ERR);
	i1 = 0;
	i2 = 0;
	while (i1 < arg_num)
	{
		g_global = false;
		if (dollar_or_not(argv1[i1], '$'))
			fill_argv_with_replaced_env(argv1[i1], argv2, &i2, envp);
		else
		{
			argv2[i2] = remove_all(argv1[i1]);
			i2++;
		}
		i1++;
	}
	argv2[i2] = NULL;
	return (argv2);
}

/*
** resets fds so that the outcome comes out from the pipe
*/

static void	reset_redirection_fds(t_fd *fds)
{
	dup2(fds->output, STDOUT_FILENO);
	dup2(fds->input, STDIN_FILENO);
	close(fds->output);
	close(fds->input);
}

void		exec_command_chunk(char *command_chunk, t_list *envp,
																bool pipe_child)
{
	t_fd	fds;
	char	**argv1;
	char	**argv2;
	char	**chunk_words;

	chunk_words = split_command_line(command_chunk);
	set_fds(&fds);
	argv2 = NULL;
	if (process_redirections(chunk_words, &fds, envp) == SUCCESS)
	{
		argv1 = extract_argv(chunk_words);
		ft_free_split(chunk_words);
		if (!is_redirection_str(argv1[0]))
		{
			argv2 = set_command_argv(argv1, envp);
			exec_command_argv(argv2, envp);
			ft_free_split(argv2);
		}
		ft_free_split(argv1);
	}
	reset_redirection_fds(&fds);
	if (pipe_child)
		exit(g_last_exit_status);
}
