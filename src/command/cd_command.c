/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:49 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/11 14:38:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	old_pwd(t_list *envp)
{
	const char	*oldpwd_key = "OLDPWD=";
	char		*pwd;
	char		*oldpwd;
	char		*buf;

	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	oldpwd = ft_strjoin(oldpwd_key, pwd);
	if (same_key(oldpwd_key, envp))
	{
		while (envp && envp->next)
		{
			if (ft_strnequal((char*)envp->content, oldpwd_key,
														ft_strlen(oldpwd_key)))
			{
				SAFE_FREE(envp->content);
				envp->content = ft_strdup(oldpwd);
			}
			envp = envp->next;
		}
	}
	else
		add_variable(oldpwd, envp);
	SAFE_FREE(oldpwd);
	SAFE_FREE(pwd);
}

static void	new_pwd(t_list *envp)
{
	const char	*pwd_key = "PWD=";
	char		*pwd;
	char		*new_pwd;
	char		*buf;

	buf = NULL;
	pwd = getcwd(buf, PATH_MAX);
	new_pwd = ft_strjoin(pwd_key, pwd);
	while (envp && envp->next)
	{
		if (ft_strnequal((char*)envp->content, pwd_key, ft_strlen(pwd_key)))
		{
			SAFE_FREE(envp->content);
			envp->content = ft_strdup(new_pwd);
		}
		envp = envp->next;
	}
	SAFE_FREE(new_pwd);
	SAFE_FREE(pwd);
}

static void	put_error(char *argv)
{
	ft_putstr("bash: cd: ");
	ft_putstr(argv);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

// static char	*find_home(t_list *envp)
// {
// 	const char	*home_key = "HOME=";
// 	char		*variable;
// 	int			count;
// 	char		*str;

// 	str = NULL;
// 	while (envp && envp->next)
// 	{
// 		if (ft_strnequal((char*)envp->content, home_key, ft_strlen(home_key)))
// 			variable = ft_strdup((char*)envp->content);
// 		envp = envp->next;
// 	}
// 	if (variable != NULL)
// 	{
// 		count = ft_strrchr_int(variable, '=');
// 		str = ft_substr_free(variable, count + 1, ft_strlen(variable) - count);
// 	}
// 	return (str);
// }

static char	*find_home(t_list *envp)
{
	const char	*home_key = "HOME=";
	char		*variable;
	int			count;
	char		*str;

	str = NULL;
	while (envp && envp->next)
	{
		if (ft_strnequal((char*)envp->content, home_key, ft_strlen(home_key)))
			variable = ft_strdup((char*)envp->content);
		envp = envp->next;
	}
	if (variable != NULL)
	{
		count = ft_strrchr_int(variable, '=');
		str = ft_substr_free(variable, count + 1, ft_strlen(variable) - count);
	}
	return (str);
}

void		cd(char **argv, t_list *envp)
{
	char	*home_key;
	char	**arg;

	home_key = find_key("HOME=", envp);
	if (!home_key && argv[1] == NULL)
	{
		SAFE_FREE(home_key);
		g_last_exit_status = EXIT_FAILURE;
		put_bash_err_msg("cd", "HOME not set");
		return ;
	}
	SAFE_FREE(home_key);
	arg = set_command_argv(argv, envp);
	old_pwd(envp);
	if ((arg[1] == NULL) || (ft_strequal(arg[1], "~")))
		arg[1] = find_home(envp);
	if (ft_strequal(arg[1], "") && !g_global)
		;
	else if (chdir(arg[1]) == ERROR)
	{
		put_error(arg[1]);
		g_last_exit_status = EXIT_FAILURE;
	}
	new_pwd(envp);
	ft_free_split(arg);
}
