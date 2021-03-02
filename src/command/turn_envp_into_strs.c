/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 08:41:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**turn_envp_into_strs(t_list *envp)
{
	size_t	index;
	char	**strs;

	index = 0;
	if (!(strs = malloc(sizeof(char *) * (ft_lstsize(envp) + 1))))
		return (NULL);
	while (envp)
	{
		strs[index] = ft_strdup((char*)envp->content);
		index++;
		envp = envp->next;
	}
	strs[index] = NULL;
	return (strs);
}
