/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:55 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/03 06:56:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	echo(t_chunk *chunk)
// {
// 	int i;

// 	i = 1;
// 	if (!ft_strcmp(chunk->argv[i], "-n"))
// 	{
// 		i++;
// 		while (chunk->argv[i] != 0)
// 		{
// 			ft_putstr_fd(chunk->argv[i++], 1);
// 			if (chunk->argv[i] != NULL)
// 				write(1, " ", 1);
// 		}
// 	}
// 	else
// 	{
// 		while (chunk->argv[i] != 0)
// 		{
// 			ft_putstr_fd(chunk->argv[i++], 1);
// 			if (chunk->argv[i] != NULL)
// 				write(1, " ", 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// }

// void	echo(t_chunk *chunk)
// {
// 	size_t	index;

// 	index = 1;
// 	if (ft_strequal(chunk->argv[index], "-n"))
// 	{
// 		index++;
// 		while (chunk->argv[index] != '\0')
// 		{
// 			ft_putstr(chunk->argv[index++]);
// 			if (chunk->argv[index] != NULL)
// 				ft_putchar(' ');
// 		}
// 	}
// 	else
// 	{
// 		if (!chunk->argv[0])
// 			ft_putchar('\0');
// 		else
// 			while (chunk->argv[index] != '\0')
// 			{
// 				ft_putstr(chunk->argv[index++]);
// 				if (chunk->argv[index] != NULL)
// 					ft_putchar(' ');
// 			}
// 		ft_putchar('\n');
// 	}
// }

void	echo(char **argv)
{
	size_t	index;

	index = 1;
	if (ft_strequal(argv[index], "-n"))
	{
		index++;
		while (argv[index] != '\0')
		{
			ft_putstr(argv[index++]);
			if (argv[index] != NULL)
				ft_putchar(' ');
		}
	}
	else
	{
		if (!argv[0])
			ft_putchar('\0');
		else
			while (argv[index] != '\0')
			{
				ft_putstr(argv[index++]);
				if (argv[index] != NULL)
					ft_putchar(' ');
			}
		ft_putchar('\n');
	}
}