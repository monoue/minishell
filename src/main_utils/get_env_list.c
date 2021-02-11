/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/11 09:45:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env_list(void)
{
	extern char	**environ;
	t_list		*envp;
	t_list		*tmp;
	size_t		index;

	if (!environ)
		return (NULL);
	envp = ft_lstnew(environ[0]);
	index = 1;
	while (environ[index])
	{
		tmp = ft_lstnew(environ[index]);
		ft_lstadd_back(&envp, tmp);
		index++;
	}
	return (envp);
}
