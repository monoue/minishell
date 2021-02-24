/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_replaced_words.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/24 09:59:54 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**get_env_replaced_words(char **words, t_list *envp)
// {
// 	const size_t	words_num = ft_count_strs((const char **)words);
// 	size_t			index;
// 	char			**replaced_words;

// 	replaced_words = ft_calloc(words_num + 1, sizeof(char *));
// 	if (!replaced_words)
// 		exit_err_msg(MALLOC_ERR);
// 	index = 0;
// 	while (index < words_num)
// 	{
// 		if (dollar_or_not(words[index], '$'))
// 			replaced_words[index] = dollar(words[index], envp);
// 		else
// 			replaced_words[index] = ft_strdup(words[index]);
// 		index++;
// 	}
// 	return (replaced_words);
// }
