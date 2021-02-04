/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:05 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:04:33 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		only_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	exit_minishell(char **argv)
{
	int		nbr;
	int		exit_nbr;

	if (argv[1] == NULL)
	{
		cat_exit();
		exit(0);
	}
	else if (only_digit(argv[1]) && argv[2] == NULL)
	{
		nbr = ft_atoi(argv[1]);
		exit_nbr = ((nbr % 256) + 256) % 256;
		cat_exit();
		exit (exit_nbr);
	}
	else if (!only_digit(argv[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else if (ft_count_strs((const char**)argv) > 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
	}
	return (0);
}
