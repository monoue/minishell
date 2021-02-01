/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:04:13 by sperrin           #+#    #+#             */
<<<<<<< HEAD:minishell/command/command/no_pipe_command.c
/*   Updated: 2021/01/27 11:32:44 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/command/no_pipe_command.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_pipe(t_chunk *chunk, t_list *envp)
{
	if (ft_strequal(chunk->argv[0], "help"))
		help();
	else if (ft_strequal(chunk->argv[0], "exit"))
		minishell_exit();
	else if (ft_strequal(chunk->argv[0], "cd"))
		cd(chunk->argv);
	else if (ft_strequal(chunk->argv[0], "pwd"))
		pwd(chunk);
	else if (ft_strequal(chunk->argv[0], "echo"))
		echo(chunk);
	else if (ft_strequal(chunk->argv[0], "env"))
		env(envp);
	else if (ft_strequal(chunk->argv[0], "export"))
		export(chunk, envp);
	else if (ft_strequal(chunk->argv[0], "unset"))
		unset(chunk, envp);
}
