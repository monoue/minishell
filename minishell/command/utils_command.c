/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:37:10 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:05:56 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// help は入れない？
const char *g_commands[] = {
	"cd",
	"help"
	"echo",
	"env",
	"exit",
	"export",
	"pwd",
	"unset",
	NULL
};

bool	arg_is_str(char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[i]))
		return (0);
	if (argv[0] == '=')
		return (0);
	return (1);
}

bool	check_valid_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '=')
		return (0);
	while (argv[i])
	{
		if (argv[i] == '=')
			return (1);
		i++;
	}
	if (argv[i] == '\0')
		return (0);
	i++;
	return (1);
}

void	ascii_sort(char **args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strcmp(args[i], args[j]) > 0)
			{
				tmp = args[i];
				args[i] = args[j];
				args[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	is_command(char *argv)
{
	size_t		index;

	index = 0;
	while (g_commands[index])
	{
		if (ft_strequal(argv, g_commands[index]))
			return (true);
		index++;
	}
	return (false);
}

bool	pipe_or_not_pipe(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if ((ft_strequal(argv[i], "|")) || (!is_command(argv[0])))
			return (1);
		i++;
	}
	return (0);
}
