/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/21 19:53:31 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_env(char *cont)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = ft_strdup(cont);
	new->next = NULL;
	return (new);
}

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
		tmp = new_env(environ[index]);
		ft_lstadd_back(&envp, tmp);
		index++;
	}
	return (envp);
}
