/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:49 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/12 15:36:48 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (str_is_of_tabs_or_spaces(str))
		SAFE_FREE(str);
	return (str);
}

void		set_home(char ***argv, t_list *envp)
{
	(*argv)[1] = find_home(envp);
	(*argv)[2] = NULL;
}
