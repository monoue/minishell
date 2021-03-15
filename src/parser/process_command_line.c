/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/13 21:56:37 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command_line(char *line, t_list *envp)
{
	char	**commands;
	size_t	index;

	commands = ft_split_skipping_quotes(line, ';');
	SAFE_FREE(line);
	if (!commands)
		exit_err_msg(MALLOC_ERR);
	index = 0;
	while (commands[index])
	{
		g_into_dollar = 0;
		process_one_command(commands[index], envp);
		if ((ft_strncmp(commands[index], "exit", 4) == 0)
			&& (ft_strncmp(commands[index + 1], " echo", 5) == 0))
			break ;
		index++;
	}
	ft_free_split(commands);
}
