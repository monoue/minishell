/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 08:41:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	same_key(const char *key, t_list *envp)
{
	size_t	count;

	count = ft_strlen(key);
	while (envp)
	{
		if (ft_strnequal((char*)envp->content, key, count))
			return (true);
		envp = envp->next;
	}
	return (false);
}
