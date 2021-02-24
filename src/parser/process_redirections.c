/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 13:26:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void					free_redirections(t_redirection_set *set)
{
	while (set)
	{
		free(set->filename);
		free(set);
		set = set->next;
	}
}

int							get_default_fd_num(t_type redirection_type)
{
	if (redirection_type == TYPE_INPUT)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int							get_fd_num(char *redirection_str, t_type redirection_type)
{
	size_t	index;

	if (!ft_isdigit(redirection_str[0]))
		return (get_default_fd_num(redirection_type));
	if (!str_is_within_int(redirection_str))
		return (OVER_INT_MAX);
	return (ft_atoi(redirection_str));
}

static t_redirection_set	*make_redirection_set(char **elements,
																t_list *envp)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	char				*filename;

	set = NULL;
	new = ft_calloc(1, sizeof(t_redirection_set));
	if (!new)
		exit_err_msg(MALLOC_ERR);
	new->type = get_redirection_type(elements[0]);
	new->fd = get_fd_num(elements[0], new->type);
	filename = elements[1];
	if (str_is_quoted(filename))
		new->filename = ft_strndup(&filename[1], ft_strlen(filename) - 2);
	else
		new->filename = ft_strdup(filename);
	lstadd_back(&set, new);
	return (set);
}

// static int					set_redirections(char **chunk_words, t_fd *fds,
// 																t_list *envp)
// {
// 	t_redirection_set	*set;
// 	int					ret;

// 	set = make_redirection_set(chunk_words, envp);
// 	if (dollar_or_not(set->filename, '$') && !dollar(set->filename, envp))
// 	{
// 		put_bash_err_msg(set->filename, AMBIGUOUS_ERR);
// 		g_last_exit_status = EXIT_FAILURE;
// 		return (ERROR);
// 	}
// 	ret = set_redirection(set, fds);
// 	if (ret == ERROR)
// 		return (ERROR);
// 	free_redirections(set);
// 	return (SUCCESS);
// }

static int					set_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	t_redirection_set	*set;
	int					ret;
	char				*replaced_filename;

	set = make_redirection_set(chunk_words, envp);
	if (dollar_or_not(set->filename, '$'))
	{
		replaced_filename = dollar(set->filename, envp);
		if (!replaced_filename)
		{
			put_bash_err_msg(set->filename, AMBIGUOUS_ERR);
			g_last_exit_status = EXIT_FAILURE;
			return (ERROR);
		}
		SAFE_FREE(set->filename);
		set->filename = ft_strdup(replaced_filename);
		SAFE_FREE(replaced_filename);
	}
	ret = set_redirection(set, fds);
	if (ret == ERROR)
		return (ERROR);
	free_redirections(set);
	return (SUCCESS);
}

int		process_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
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
