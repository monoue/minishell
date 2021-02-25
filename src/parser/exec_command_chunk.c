/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 09:39:46 by monoue           ###   ########.fr       */
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

char		*remove_all(char *argv)
{
	int		index;
	char	*tmp;
	char	*str;
	char 	*arg;

	index = 0;
	tmp = NULL;
	str = ft_strdup(argv);
	if (g_global == 0)
		tmp = remove_quotes(str);
	if (g_global == 0 && ((argv[0] != '\"' && argv[0] != '\'')
		|| ((argv[0] == '\"' && argv[1] == '\"')
		|| (argv[0] == '\'' && argv[1] == '\''))))
		arg = remove_escape(tmp);
	else if (g_global == 0 && argv[0] != '\'')
		arg = remove_escape_dq(tmp);
	else
		arg = ft_strdup(tmp);
	SAFE_FREE(str);
	SAFE_FREE(tmp);
	return (arg);
}

static char	**set_command_argv(char **argv1, t_list *envp)
{
	char	**argv2;
	char	**tmp;
	size_t	index;
	int		j;
	int		i;

	g_space = 0;
	tmp = NULL;
	if (!(argv2 = malloc(sizeof(*argv2) * (MAX_INPUT))))
		exit_err_msg(MALLOC_ERR);
	if (!argv2)
		exit_err_msg(MALLOC_ERR);
	index = 0;
	i = 0;
	while (argv1[i])
	{
		g_global = 0;
		if (dollar_or_not(argv1[i], '$'))
		{
			argv2[index] = dollar(argv1[i], envp);
			while (argv2[index] == NULL && argv1[i + 1] != NULL)
			{
				i++;
				if (dollar_or_not(argv1[i], '$'))
					argv2[index] = dollar(argv1[i], envp);
			}
			if (argv2[index] != NULL && g_flag_escape_db == 0
				&& g_flag_dont == 1)
			{
				tmp = ft_split(argv2[index], ' ');
				j = 0;
				if (tmp[j] != NULL)
				{
					while (tmp[j])
					{
						free(argv2[index]);
						argv2[index] = tmp[j];
						index++;
						j++;
					}
				}
			// ft_free_split(tmp);
			}
		}
		else
		{
			argv2[index] = remove_all(argv1[i]);
			index++;
		}
		i++;
	}
	return (argv2);
}

// static void	reset_redirection_fds(t_fd fds)
// {
// 	if (fds.input != STDIN_FILENO)
// 	{
// 		dup2(fds.input, STDIN_FILENO);
// 		close(fds.input);
// 	}
// 	if (fds.output > 2)
// 	{
// 		dup2(fds.output, STDOUT_FILENO);
// 		close(fds.output);
// 	}
// }

/*
** resets fds so that the outcome comes out from the pipe
*/

static void	reset_redirection_fds(t_fd fds)
{
	// TODO: 復活させるべき
	// これがないと、閉じない
	dup2(fds.output, STDOUT_FILENO);
	dup2(fds.input, STDIN_FILENO);
	close(fds.output);
	close(fds.input);
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
	reset_redirection_fds(fds);
	if (pipe_child)
		exit(g_last_exit_status);
}
