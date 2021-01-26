/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:55 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/26 17:40:56 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_chunk *chunk)
{
	int i;

	i = 1;
	if (!ft_strcmp(chunk->argv[i], "-n"))
	{
		i++;
		while (chunk->argv[i] != 0)
		{
			ft_putstr_fd(chunk->argv[i++], 1);
			if (chunk->argv[i] != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (chunk->argv[i] != 0)
		{
			ft_putstr_fd(chunk->argv[i++], 1);
			if (chunk->argv[i] != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}
