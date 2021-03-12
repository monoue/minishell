/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:37:10 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 08:25:15 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_valid_arg(char *argv)
{
	size_t	index;

	if (argv[0] == '=')
		return (false);
	index = 1;
	while (argv[index])
	{
		if (argv[index] == '=')
			return (true);
		index++;
	}
	if (argv[index] == '\0')
		return (false);
	return (true);
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

bool	ft_str_is_numeric_bis(const char *str)
{
	size_t	index;
	size_t	i;
	size_t	length;

	index = 0;
	i = 0;
	length = ft_strlen(str);
	length--;
	while (str[length] == ' ')
	{
		i++;
		length--;
	}
	while (str[index] != '\0' && ft_isdigit(str[index]) && str[index] != ' ')
	{
		if (str[index] != ' ')
			index++;
	}
	return (index == ft_strlen(str) - i);
}
