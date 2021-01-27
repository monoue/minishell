/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:01 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/27 11:32:34 by monoue           ###   ########.fr       */
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
