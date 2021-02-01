/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:01 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/01 06:33:44 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_list *envp)
{
	while (envp)
	{
		ft_putendl_fd(envp->content, STDOUT_FILENO);
		envp = envp->next;
	}
}
