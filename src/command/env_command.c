/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:01 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/26 14:08:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *envp)
{
	if (envp->content == NULL)
		return ;
	while (envp && envp->next != NULL)
	{
		ft_putendl(envp->content);
		envp = envp->next;
	}
	if (envp)
		ft_putendl(envp->content);
}
