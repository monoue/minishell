/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_num_is_over_llong_max.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:41:39 by monoue            #+#    #+#             */
/*   Updated: 2021/03/08 12:40:17 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		digits_num_is_over_llong_max(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] == '0')
		index++;
	return (ft_strlen(&str[index]) > LLONG_MAX_DIGITS);
}

char		*plus_or_not(char *arg)
{
	char	*argv;

	argv = NULL;
	if (g_plus == 0)
		argv = ft_strdup(arg);
	else if (g_plus == 1)
		argv = skip_plus(arg, 0, 0);
	return (argv);
}

void		remplace_value(char *arg, t_list *envp, int i)
{
	const int	len = ft_strlen(arg);

	while (i < len && arg[i] != '=')
		i++;
	i++;
	if (i > len)
		;
	else if (g_plus == 1)
		envp->content = ft_strjoin_free(envp->content, &arg[i]);
	else if (g_plus == 0)
	{
		SAFE_FREE(envp->content);
		envp->content = ft_strdup(arg);
	}
	return ;
}

void		error_cd(char *home_key)
{
	SAFE_FREE(home_key);
	g_last_exit_status = EXIT_FAILURE;
	put_bash_err_msg("cd", "HOME not set");
}
