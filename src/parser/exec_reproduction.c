/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reproduction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2021/03/14 12:01:49 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char		*remove_all_bis(char *argv)
{
	char	*arg;
	char	*arg_tmp;

	arg_tmp = remove_escape(argv, 0);
	if (g_escape == 0 && g_into_dollar == 0)
		arg = remove_quotes(arg_tmp);
	else
		arg = ft_strdup(arg_tmp);
	SAFE_FREE(arg_tmp);
	return (arg);
}

static void	exec_not_exit_reproduction(char **argv, t_list *envp)
{
	char	*home_key;
	char	*arg;

	arg = remove_all_bis(argv[0]);
	home_key = NULL;
	if (ft_strequal(arg, "cd"))
		cd(argv, envp, home_key);
	else if (ft_strequal(arg, "pwd"))
		pwd(argv);
	else if (ft_strequal(arg, "echo"))
		echo(argv);
	else if (ft_strequal(arg, "env"))
		env(envp);
	else if (ft_strequal(arg, "export"))
		export(argv, envp);
	else if (ft_strequal(arg, "unset"))
		unset(argv, envp);
	else
	{
		g_last_exit_status = 127;
		put_bash_err_msg(arg, NO_COMMANDS_ERR);
		SAFE_FREE(arg);
	}
	SAFE_FREE(arg);
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
