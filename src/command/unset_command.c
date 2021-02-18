/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/18 16:39:29 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t		index;
	const char	*ng_chars = "$~-#*%()/|<+[]{}:;@?^!\'\"";

	if (arg[0] == '=')
		return (false);
	index = 0;
	if (arg[index] == 0)
		return (false);
	while (arg[index])
	{
		if (arg[index] == '=')
			return (true);
		if (ft_strchr(ng_chars, arg[index]) || ft_isdigit(arg[index]))
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
	target_prev_i = get_target_prev_i(key, envp);
	while (env_i < target_prev_i)
	{
		envp = envp->next;
		env_i++;
	}
	if (env_i == 0)
		envp = envp->next;
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
	while (argv[arg_i])
	{
		if (!is_valid_arg1(argv[arg_i]))
		{
			put_error_invalid_identifier("unset", argv[arg_i]);
			arg_i++;
			continue ;
		}
		key = get_key(argv[arg_i]);
		if (same_key(key, envp))
			unset_key(key, envp);
		SAFE_FREE(key);
		arg_i++;
	}
}
