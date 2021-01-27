/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:37:10 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		arg_is_str(char *argv)
{
	int	i;

	i = 0;
	if (ft_isdigit(argv[i]))
		return (0);
	if (argv[0] == '=')
		return (0);
	return (1);
}

int		check_valid_arg(char *argv)
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
	// if (argv[i] == ' ') je pense pas en avoir besoin
	//     return (0);
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

int		check_command(char *argv)
{
	if ((strcmp(argv, "pwd") == 0) || (strcmp(argv, "cd") == 0)
	|| (strcmp(argv, "echo") == 0)
	|| (strcmp(argv, "env") == 0) || (strcmp(argv, "export") == 0)
	|| (strcmp(argv, "unset") == 0) || (strcmp(argv, "exit") == 0))
		return (1);
	return (0);
}

int		pipe_or_not_pipe(t_chunk *chunk)
{
	int		i;

	i = 0;
	while (chunk->argv[i])
	{
		if ((ft_strcmp(chunk->argv[i], "|") == 0)
		|| (check_command(chunk->argv[0]) == 0))
			return (1);
		i++;
	}
	return (0);
}
