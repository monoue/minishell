/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/03/03 06:44:58 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirections(t_redirection_set *set)
{
	while (set)
	{
		free(set->filename);
		free(set);
		set = set->next;
	}
}

static bool	redirection_filename_is_ambiguous(char *filename)
{
	char	**words;
	size_t	words_num;

	if (!filename)
		return (true);
	words = split_command_line(filename);
	words_num = ft_count_strs((const char **)words);
	ft_free_split(words);
	return (words_num > 1);
}

static int	set_redirections(char **chunk_words, t_fd *fds, t_list *envp)
{
	t_redirection_set	*set;
	char				*replaced_filename;
	char				**argv;

	argv = set_command_argv(chunk_words, envp);
	set = make_redirection_set(argv);
	ft_free_split(argv);
	if (dollar_or_not(set->filename, '$'))
	{
		replaced_filename = dollar(set->filename, envp);
		if (redirection_filename_is_ambiguous(replaced_filename))
		{
			put_bash_err_msg(set->filename, AMBIGUOUS_ERR);
			g_last_exit_status = EXIT_FAILURE;
			return (ERROR);
		}
		SAFE_FREE(set->filename);
		set->filename = ft_strdup(replaced_filename);
		SAFE_FREE(replaced_filename);
	}
	if (set_redirection(set, fds) == ERROR)
		return (ERROR);
	free_redirections(set);
	return (SUCCESS);
}

int			process_redirections(char **chunk_words, t_fd *fds, t_list *envp)
{
	const size_t	words_num = ft_count_strs((const char **)chunk_words);
	size_t			index;
	int				ret;

	index = 0;
	while (index < words_num)
	{
		if (is_redirection_str(chunk_words[index]))
		{
			ret = set_redirections(&chunk_words[index], fds, envp);
			if (ret == ERROR)
				return (ERROR);
			index += 2;
		}
		else
			index++;
	}
	return (SUCCESS);
}
