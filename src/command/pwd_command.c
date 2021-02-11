/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:21 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/11 10:29:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pwd(char **argv)
{
	if (argv[1])
		{
			ft_putstr("pwd: too many arguments\n");
			exit(EXIT_FAILURE);
		}
		ft_putstr(getcwd(NULL, 0));
		ft_putchar('\n');
}
