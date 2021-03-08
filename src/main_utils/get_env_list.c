/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/03/09 08:38:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*new_env(char *cont)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		exit_err_msg(MALLOC_ERR);
	new->content = ft_strdup(cont);
	new->next = NULL;
	return (new);
}

static bool		has_underscore_env(char **environ)
{
	const size_t	environ_num = ft_count_strs((const char **)environ);
	size_t			index;

	index = 0;
	while (index < environ_num)
	{
		if (ft_strnequal(environ[index], "_=", 2))
			return (true);
		index++;
	}
	return (false);
}

static t_list	*make_shelllevel_and_underscore(void)
{
	t_list	*envp;
	t_list	*tmp;
	char	*str;
	char	buf[1024 + 1];

	envp = NULL;
	str = ft_strdup("PWD=");
	getcwd(buf, 1024);
	str = ft_strjoin_free(str, buf);
	tmp = new_env(str);
	ft_lstadd_back(&envp, tmp);
	tmp = new_env("SHLVL=1");
	ft_lstadd_back(&envp, tmp);
	tmp = new_env("_=./minishell");
	ft_lstadd_back(&envp, tmp);
	return (envp);
}

t_list			*get_env_list(void)
{
	extern char	**environ;
	t_list		*envp;
	t_list		*tmp;
	size_t		index;

	envp = NULL;
	if (!environ[0])
		return (make_shelllevel_and_underscore());
	envp = new_env(environ[0]);
	if (!has_underscore_env(environ))
	{
		tmp = new_env("_=./minishell");
		ft_lstadd_back(&envp, tmp);
	}
	index = 1;
	while (environ[index])
	{
		tmp = new_env(environ[index]);
		ft_lstadd_back(&envp, tmp);
		index++;
	}
	change_shlvl(envp);
	return (envp);
}
