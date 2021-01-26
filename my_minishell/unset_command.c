/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/26 18:40:16 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_chunk *chunk, t_list *envp)
{
	int		i;
	int		count;
	char	*key;
	char	*new;
	char	*tmp;

	i = 1;
	while (chunk->argv[i])
	{
		count = ft_strlen(chunk->argv[i]);
		if (same_key(chunk->argv[i], envp) == 1)
		{
			while (envp && envp->next)
			{
				tmp = envp->content;
				if (ft_strncmp(tmp, chunk->argv[i], count) == 0)
				{
					delete_variable(envp->content);
				}
				envp = envp->next;
			}
		}
		i++;
	}
}
