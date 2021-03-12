/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:30:52 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 13:01:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*find_arg(t_list *envp)
{
	t_list	*tmp;
	char	*arg;

	arg = NULL;
	tmp = envp;
	while (tmp)
	{
		if (ft_strnequal((char*)(tmp->content), "SHLVL=", ft_strlen("SHLVL=")))
			arg = ft_strdup((char*)tmp->content);
		tmp = tmp->next;
	}
	SAFE_FREE(tmp);
	return (arg);
}

char			*get_value(char *value)
{
	int		int_value;
	char	*str;

	if (!value)
		return (NULL);
	if (!ft_isdigit(value[0]))
	{
		int_value = 1;
		value = ft_itoa(int_value);
		return (value);
	}
	int_value = ft_atoi(value);
	if (int_value > 999)
		int_value = 1;
	if (int_value < 0)
		int_value = 0;
	if (int_value == 999)
		return (NULL);
	int_value += 1;
	str = ft_itoa(int_value);
	return (str);
}

char			*replace_shlvl_value(char *arg, int i, char *value)
{
	char	*key;
	char	*str;

	if (!arg)
		return (NULL);
	if (!(key = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	while (arg[i] != '=')
	{
		key = ft_strnjoin_free(key, &arg[i], 1);
		i++;
	}
	key = ft_strnjoin_free(key, &arg[i], 1);
	i++;
	while (arg[i])
	{
		value = ft_strnjoin_free(value, &arg[i], 1);
		i++;
	}
	str = get_value(value);
	key = ft_strjoin_free_both(key, str);
	SAFE_FREE(value);
	return (key);
}

void			change_shlvl(t_list *envp)
{
	char	*arg;
	char	*key;
	char	*value;

	arg = find_arg(envp);
	if (!arg)
		return ;
	if (!(value = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	key = replace_shlvl_value(arg, 0, value);
	while (envp)
	{
		if (ft_strnequal((char*)(envp->content), "SHLVL=", ft_strlen("SHLVL=")))
		{
			SAFE_FREE(envp->content);
			envp->content = ft_strdup(key);
		}
		envp = envp->next;
	}
	SAFE_FREE(arg);
	SAFE_FREE(key);
}
