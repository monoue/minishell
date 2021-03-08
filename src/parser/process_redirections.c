/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/03/08 11:30:42 by monoue           ###   ########.fr       */
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

static bool	redirection_filename_is_ambiguous(char *filename, t_list *envp)
{
	char	**words;
	size_t	words_num;
	char	*replaced_filename;

	if (!filename)
		return (true);
	if (!has_dollar_variable(filename) || str_is_quoted_by_double(filename))
		return (false);
	replaced_filename = dollar(filename, envp);
	if (!replaced_filename)
		return (true);
	words = split_command_line(replaced_filename);
	SAFE_FREE(replaced_filename);
	words_num = ft_count_strs((const char **)words);
	ft_free_split(words);
	return (words_num != 1);
}

static int	set_redirections(char **chunk_words, t_fd *fds, t_list *envp)
{
	t_redirection_set	*set;
	char				*replaced_filename;
	const char			*filename_before_conv = chunk_words[1];

	if (redirection_filename_is_ambiguous((char *)filename_before_conv, envp)
						|| ft_strequal((char *)filename_before_conv, "\"\""))
	{
		if (ft_strequal((char *)filename_before_conv, "\"\""))
			put_bash_err_msg(filename_before_conv, strerror(ENOENT));
		else
			put_bash_err_msg(filename_before_conv, AMBIGUOUS_ERR);
		g_last_exit_status = EXIT_FAILURE;
		return (ERROR);
	}
	set = make_redirection_set(chunk_words);
	if (has_dollar_variable(set->filename))
	{
		replaced_filename = dollar(set->filename, envp);
		SAFE_FREE(set->filename);
		set->filename = ft_strdup_free(replaced_filename);
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
