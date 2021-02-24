/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:21 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/24 16:07:22 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pwd(char **argv)
{
	if (argv[1])
	{
		ft_putstr("pwd: too many arguments\n");
		g_last_exit_status = EXIT_FAILURE;
		return ;
	}
	ft_putstr(getcwd(NULL, 0));
	ft_putchar('\n');
}
