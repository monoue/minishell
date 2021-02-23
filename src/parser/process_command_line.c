/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:25:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/21 12:00:21 by sperrin          ###   ########.fr       */
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
		process_one_command(commands[index], envp);
		index++;
	}
	ft_free_split(commands);
}
