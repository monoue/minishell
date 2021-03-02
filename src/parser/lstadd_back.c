/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:48:44 by monoue            #+#    #+#             */
/*   Updated: 2021/03/03 08:47:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirection_set	*lstlast(t_redirection_set *set)
{
	if (!set)
		return (NULL);
	while (set->next)
		set = set->next;
	return (set);
}

void						lstadd_back(t_redirection_set **sets,
														t_redirection_set *new)
{
	t_redirection_set	*set;

	if (!sets || !new)
		return ;
	if (!(*sets))
	{
		*sets = new;
		return ;
	}
	set = lstlast(*sets);
	set->next = new;
}
