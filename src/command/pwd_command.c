/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:21 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/27 10:51:02 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pwd(char **argv)
{
	char *arg;
	if (argv[1])
	{
		ft_putstr("pwd: too many arguments\n");
		g_last_exit_status = EXIT_FAILURE;
		return ;
	}
	arg = getcwd(NULL, 0);
	ft_putstr(arg);
	ft_putchar('\n');
	free(arg);
}
