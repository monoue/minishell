/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/02/21 20:24:11 by sperrin          ###   ########.fr       */
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

static t_redirection_set	*make_redirection_list(char **elements,
																t_list *envp)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	size_t				index;
	char				*filename;

	index = 0;
	set = NULL;
	while (elements[index])
	{
		new = ft_calloc(1, sizeof(t_redirection_set));
		if (!new)
			exit_err_msg(MALLOC_ERR);
		new->type = get_redirection_type(elements[index]);
		filename = elements[index + 1];
		if (dollar_or_not(filename, '$')
			&& dollar(filename, envp)[0] == '\0')
			exit_bash_err_msg(filename, AMBIGUOUS_ERR, EXIT_FAILURE);
		new->filename = ft_strdup(filename);
		lstadd_back(&set, new);
		index += 2;
	}
	return (set);
}

static void					set_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	t_redirection_set	*set;
	t_redirection_set	*tmp;

	set = make_redirection_list(chunk_words, envp);
	tmp = set;
	while (set)
	{
		set_redirection(set, fds);
		set = set->next;
	}
	free_redirections(tmp);
}

size_t						process_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	size_t	index;

	index = 0;
	while (chunk_words[index])
	{
		if (is_redirection_str(chunk_words[index]))
		{
			set_redirections(&chunk_words[index], fds, envp);
			break ;
		}
		index++;
	}
	return (index);
}
