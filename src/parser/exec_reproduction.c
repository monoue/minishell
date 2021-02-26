/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reproduction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/02/26 14:08:05 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	exec_reproduction(char **argv, t_list *envp)
{
	g_last_exit_status = EXIT_SUCCESS;
	if (ft_strequal(argv[0], "exit"))
		exit_minishell(argv);
	else if (ft_strequal(argv[0], "cd"))
		cd(argv, envp);
	else if (ft_strequal(argv[0], "pwd"))
		pwd(argv);
	else if (ft_strequal(argv[0], "echo"))
		echo(argv);
	else if (ft_strequal(argv[0], "env"))
		env(envp);
	else if (ft_strequal(argv[0], "export"))
		export(argv, envp);
	else if (ft_strequal(argv[0], "unset"))
		unset(argv, envp);
}
