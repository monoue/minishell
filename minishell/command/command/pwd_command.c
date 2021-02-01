/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:21 by sperrin           #+#    #+#             */
<<<<<<< HEAD:minishell/command/command/pwd_command.c
/*   Updated: 2021/01/27 11:32:46 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/command/pwd_command.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_chunk *chunk)
{
	if (chunk->argv[1])
	{
		ft_putstr("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	ft_putendl(getcwd(NULL, 0));
}
