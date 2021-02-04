/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:55 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:04:14 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **argv)
{
	int i;

	i = 1;
	if (argv[i] == NULL)
	{
		write(1, " ", 1);
		write(1, "\n", 1);
		return ;
	}
	if (!ft_strcmp(argv[i], "-n"))
	{
		i++;
		while (argv[i] != 0)
		{
			ft_putstr_fd(argv[i++], 1);
			if (argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (argv[i] != 0)
		{
			ft_putstr_fd(argv[i++], 1);
			if (argv[i] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
