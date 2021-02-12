/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:55 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/12 13:09:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool		is_option_n(char *str)
{
	size_t	index;

	if (!str || !ft_strnequal(str, "-n", 2))
		return (false);
	index = 2;
	while (str[index])
	{
		if (str[index] != 'n')
			return (false);
		index++;
	}
	return (true);
}

static size_t	skip_options(char **argv, bool *option_n)
{
	size_t	index;

	if (!is_option_n(argv[1]))
	{
		*option_n = false;
		return (1);
	}
	*option_n = true;
	index = 2;
	while (argv[index] && is_option_n(argv[index]))
		index++;
	return (index);
}

static void		put_echo_targets(char **targets)
{
	size_t	index;

	index = 0;
	while (targets[index])
	{
		if (index != 0)
			ft_putchar(' ');
		ft_putstr(targets[index]);
		index++;
	}
}

void			echo(char **argv)
{
	size_t	index;
	bool	option_n;

	if (!argv[1])
	{
		ft_putendl(" ");
		return ;
	}
	index = skip_options(argv, &option_n);
	put_echo_targets(&argv[index]);
	if (!option_n)
		ft_putchar('\n');
}
