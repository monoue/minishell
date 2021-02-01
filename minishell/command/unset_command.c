/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/01 06:34:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_chunk *chunk, t_list *envp)
{
	size_t	index;
	char	*key;
	char	*new;
	char	*tmp;

	index = 1;
	while (chunk->argv[index])
	{
		if (is_key_duplicated(chunk->argv[index], envp))
		{
			while (envp && envp->next)
			{
				tmp = envp->content;
				if (ft_strequal(tmp, chunk->argv[index]))
					delete_variable(envp->content);
				envp = envp->next;
			}
		}
		index++;
	}
}
