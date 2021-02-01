/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:01 by sperrin           #+#    #+#             */
<<<<<<< HEAD:minishell/command/command/env_command.c
/*   Updated: 2021/01/27 11:32:34 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/command/env_command.c
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
