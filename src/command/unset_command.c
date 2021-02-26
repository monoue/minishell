/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/25 17:58:53 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			get_target_prev_i(char *key, t_list *envp)
{
	const size_t	len = ft_strlen(key);
	size_t			index;

	index = 0;
	while (envp)
	{
		if (ft_strnequal((char*)envp->content, key, len))
			return (index - 1);
		envp = envp->next;
		index++;
	}
	return (index);
}

static bool			is_valid_arg1(char *arg)
{
	const size_t	len = ft_strlen(arg);
	size_t			index;

	if (len == 0 || arg[0] == '=' || ft_strchr(arg, '\\') || ft_isdigit(arg[0]))
		return (false);
	index = 0;
	while (index < len && arg[index] != '=')
	{
		if (!ft_isalnum(arg[index]) && arg[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

void				unset_key(char *key, t_list *envp)
{
	int		target_prev_i;
	int		env_i;
	t_list	*target;

	env_i = 0;
	target = NULL;
	if (envp == NULL)
		return ;
	if (ft_strncmp(key, "_=", 2) == 0 || ft_strncmp(key, "_", 1) == 0)
		return ;
	target_prev_i = get_target_prev_i(key, envp);
	if (target_prev_i == -1)
	{
		target = envp;
		target->content = target->next->content;
		target->next = target->next->next;
		SAFE_FREE(target);
		return ;
	}
	while (env_i < target_prev_i)
	{
		envp = envp->next;
		env_i++;
	}
	target = envp->next;
	envp->next = target->next;
	SAFE_FREE(target);
}

void				unset(char **argv, t_list *envp)
{
	int		arg_i;
	char	*key;

	arg_i = 1;
	key = NULL;
	if (envp == NULL)
		return ;
	while (argv[arg_i])
	{
		key = get_key(argv[arg_i]);
		if (!is_valid_arg1(key))
		{
			put_error_invalid_identifier("unset", argv[arg_i]);
			arg_i++;
			continue ;
		}
		if (same_key(key, envp))
			unset_key(key, envp);
		SAFE_FREE(key);
		arg_i++;
	}
}
