/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:18 by monoue            #+#    #+#             */
/*   Updated: 2021/03/01 14:00:36 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_command_line_with_quotes(char const *str)
{
	char	**words;
	size_t	words_num;

	if (!str)
		return (NULL);
	words_num = count_command_line_words(str);
	words = malloc(sizeof(*words) * (words_num + 1));
	if (!words)
		exit_err_msg(MALLOC_ERR);
	set_words(str, words, words_num);
	return (words);
}

char		**split_command_line(char const *str)
{
	char	**words;

	g_global = false;
	words = split_command_line_with_quotes(str);
	if (!words)
		return (NULL);
	return (words);
}
