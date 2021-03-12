/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reproduction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 22:30:56 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	exec_not_exit_reproduction(char **argv, t_list *envp)
{
	char	*home_key;

	home_key = NULL;
	if (ft_strequal(argv[0], "cd"))
		cd(argv, envp, home_key);
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
	else
	{
		g_last_exit_status = 127;
		put_bash_err_msg(argv[0], NO_COMMANDS_ERR);
	}
}

void		exec_reproduction(char **argv, t_list *envp, bool pipe_child)
{
	char		*quotes_trimmed_str;

	if (g_global)
	{
		quotes_trimmed_str = get_continuous_quotes_trimmed_str(argv[0]);
		SAFE_FREE(argv[0]);
		argv[0] = ft_strdup_free(quotes_trimmed_str);
	}
	if (ft_strequal(argv[0], "exit"))
		return (exit_minishell(argv, envp, pipe_child));
	g_last_exit_status = EXIT_SUCCESS;
	exec_not_exit_reproduction(argv, envp);
}
