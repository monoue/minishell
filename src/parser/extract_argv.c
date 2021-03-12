/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:49:01 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 22:14:31 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_argv(char **chunk_words)
{
	const size_t	words_num = ft_count_strs((const char **)chunk_words);
	size_t			index;
	size_t			count;

	count = 0;
	index = 0;
	while (index < words_num)
	{
		if (is_redirection_str(chunk_words[index]))
			index += 2;
		else
		{
			count++;
			index++;
		}
	}
	return (count);
}

char			**extract_argv(char **chunk_words)
{
	const size_t	words_num = ft_count_strs((const char **)chunk_words);
	const size_t	argv_num = count_argv(chunk_words);
	char			**argv;
	size_t			index;
	size_t			arg_i;

	argv = ft_calloc(argv_num + 1, sizeof(char *));
	if (!argv)
		exit_err_msg(MALLOC_ERR);
	index = 0;
	arg_i = 0;
	while (index < words_num)
	{
		if (is_redirection_str(chunk_words[index]))
			index += 2;
		else
		{
			argv[arg_i] = ft_strdup(chunk_words[index]);
			arg_i++;
			index++;
		}
	}
	return (argv);
}
