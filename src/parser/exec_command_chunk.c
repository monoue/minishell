/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 13:02:09 by monoue           ###   ########.fr       */
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

char        *remove_all(char *argv)
{
    int        index;
    char    *tmp;
    char    *str;
    char     *arg;

    index = 0;
    str = ft_strdup(argv);
    if (g_global == 0)
        tmp = remove_quotes(str);
    if (g_global == 0 && ((argv[0] != '\"' && argv[0] != '\'')
        || ((argv[0] == '\"' && argv[1] == '\"')
        || (argv[0] == '\'' && argv[1] == '\''))))
        arg = remove_escape(tmp);
    else if (g_global == 0 && argv[0] != '\'')
        arg = remove_escape_dq(tmp);
    SAFE_FREE(str);
    SAFE_FREE(tmp);
    return (arg);
}

static char	**set_command_argv(char **argv1, t_list *envp)
{
	const size_t	args_num = ft_count_strs((const char **)argv1);
	char	**argv2;
	char	**tmp;
	size_t	index;
	int		j;

	g_space = 0;
	argv2 = ft_calloc(args_num + 1, sizeof(char*));
	if (!argv2)
		exit_err_msg(MALLOC_ERR);
	// if (args_num < 2)
	// {
	// 	argv2[0] = ft_strdup(argv1[0]);
	// 	return (argv2);
	// }
	index = 0;
	while (index < args_num)
	{
		g_global = 0;
		if (dollar_or_not(argv1[index], '$'))
			argv2[index] = dollar(argv1[index], envp);
		else
			argv2[index] = remove_all(argv1[index]);
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

void		exec_command_chunk(char *command_chunk, t_list *envp,
																bool pipe_child)
{
	t_fd	fds;
	size_t	args_num;
	char	**argv1;
	char	**argv2;
	char	**chunk_words;

	chunk_words = split_command_line(command_chunk, envp);
	set_fds(&fds);
	if (process_redirections(chunk_words, &fds, envp) == SUCCESS)
	{
		argv1 = extract_argv(chunk_words);
		ft_free_split(chunk_words);

		if (!is_redirection_str(argv1[0]))
		{
			argv2 = set_command_argv(argv1, envp);
			exec_command_argv(argv2, envp);
		}
		ft_free_split(argv1);
		ft_free_split(argv2);
	}
	reset_redirection_fds(fds);
	if (pipe_child)
		exit(g_last_exit_status);
}
