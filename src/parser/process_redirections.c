/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:03 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 11:06:42 by monoue           ###   ########.fr       */
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

// static t_redirection_set	*make_redirection_list(char **elements,
// 																t_list *envp)
// {
// 	t_redirection_set	*set;
// 	t_redirection_set	*new;
// 	size_t				index;
// 	char				*filename;

// 	index = 0;
// 	set = NULL;
// 	while (elements[index])
// 	{
// 		new = ft_calloc(1, sizeof(t_redirection_set));
// 		if (!new)
// 			exit_err_msg(MALLOC_ERR);
// 		new->type = get_redirection_type(elements[index]);
// 		filename = elements[index + 1];
// 		if (dollar_or_not(filename, '$')
// 			&& dollar(filename, envp)[0] == '\0')
// 			exit_bash_err_msg(filename, AMBIGUOUS_ERR, EXIT_FAILURE);
// 		new->filename = ft_strdup(filename);
// 		lstadd_back(&set, new);
// 		index += 2;
// 	}
// 	return (set);
// }

// static void					set_redirections(char **chunk_words, t_fd *fds,
// 																t_list *envp)
// {
// 	t_redirection_set	*set;
// 	t_redirection_set	*tmp;

// 	set = make_redirection_list(chunk_words, envp);
// 	tmp = set;
// 	while (set)
// 	{
// 		set_redirection(set, fds);
// 		set = set->next;
// 	}
// 	free_redirections(tmp);
// }

// size_t						process_redirections(char **chunk_words, t_fd *fds,
// 																t_list *envp)
// {
// 	size_t	index;

// 	index = 0;
// 	while (chunk_words[index])
// 	{
// 		if (is_redirection_str(chunk_words[index]))
// 		{
// 			set_redirections(&chunk_words[index], fds, envp);
// 			break ;
// 		}
// 		index++;
// 	}
// 	return (index);
// }

// static t_redirection_set	*make_redirection_list(char **elements,
// 																t_list *envp)
static t_redirection_set	*make_redirection_set(char **elements,
																t_list *envp)
{
	t_redirection_set	*set;
	t_redirection_set	*new;
	// size_t				index;
	char				*filename;

	// index = 0;
	set = NULL;
	// while (elements[index])
	// {
		new = ft_calloc(1, sizeof(t_redirection_set));
		if (!new)
			exit_err_msg(MALLOC_ERR);
		new->type = get_redirection_type(elements[0]);
		filename = elements[1];
		if (dollar_or_not(filename, '$')
			&& dollar(filename, envp)[0] == '\0')
			exit_bash_err_msg(filename, AMBIGUOUS_ERR, EXIT_FAILURE);
		new->filename = ft_strdup(filename);
		lstadd_back(&set, new);
	// 	index += 2;
	// }
	return (set);
}

static void					set_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	t_redirection_set	*set;
	// t_redirection_set	*tmp;

	set = make_redirection_set(chunk_words, envp);
	// tmp = set;
	// while (set)
	// {
	set_redirection(set, fds);
	// 	set = set->next;
	// }
	// free_redirections(tmp);
	free_redirections(set);
}


size_t						process_redirections(char **chunk_words, t_fd *fds,
																t_list *envp)
{
	const size_t	words_num = ft_count_strs((const char **)chunk_words);
	size_t			index;

	index = 0;
	while (index < words_num)
	{
		if (is_redirection_str(chunk_words[index]))
		{
			// 1 セットずつ処理することとする
			set_redirections(&chunk_words[index], fds, envp);
			index += 2;
		}
		else
			index++;
	}
	return (index);
}
