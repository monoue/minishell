/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:21:58 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/16 19:21:01 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *arg, t_list *envp)
{
	char	*variable;
	t_list	*tmp_list;

	if (!(variable = ft_strdup("")))
		exit_err_msg(MALLOC_ERR);
	tmp_list = envp;
	while (tmp_list && tmp_list->next)
	{
		if (ft_strncmp((char*)tmp_list->content, arg, ft_strlen(arg)) == 0)
			variable = ft_strnjoin_free(variable,
			(char*)tmp_list->content, ft_strlen((char*)tmp_list->content));
		tmp_list = tmp_list->next;
	}
	if (!variable)
		return (NULL);
	return (variable);
}
