/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 21:04:22 by sperrin          ###   ########.fr       */
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
}

char		*remove_all(char *argv)
{
	int		index;
	char	*tmp;
	char	*str;
	
	index = 0;
	str = ft_strdup(argv);
	if (g_global == 0)
			tmp = remove_quotes(str);
	if (g_global == 0 && argv[0] != '\"')
		tmp = remove_escape(str);
	else if (g_global == 0 && argv[0] != '\"' 
			&& argv[0] != '\'')
		tmp = remove_escape_dq(str);
	SAFE_FREE(str);
	return (tmp);
}

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
		g_global = 0;
		if (dollar_or_not(chunk_words[index], '$'))
			argv[index] = dollar(chunk_words[index], envp);
		else
			argv[index] = remove_all(chunk_words[index]);
		// if (argv[index] != NULL && argv[index][0] == '\"' && argv[index][1] == ' ' 
		// 		&& argv[index][2] != '\'')
		// {
		// 	tmp = ft_split(argv[index], ' ');
		// 	j = 0;
		// 	while (tmp[j])
		// 	{
		// 		free(argv[index]);
		// 		argv[index] = tmp[j];
		// 		index++;
		// 		j++;
		// 	}
		// 	ft_free_split(tmp);
		// }
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

	chunk_words = split_command_line(command_chunk, envp);
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
