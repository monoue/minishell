/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:01 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/26 17:49:38 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *envp)
{
	while (envp && envp->next != NULL)
	{
		ft_putendl_fd(envp->content, 1);
		envp = envp->next;
	}
	if (envp)
		ft_putendl_fd(envp->content, 1);
}
