/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:16:21 by monoue            #+#    #+#             */
/*   Updated: 2020/07/03 14:58:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*newl;
	t_list	*new_start;

	if (!lst || !f)
		return (NULL);
	l = lst;
	newl = ft_lstnew(f(l->content));
	if (newl == NULL)
		return (NULL);
	new_start = newl;
	while (l->next)
	{
		l = l->next;
		newl->next = ft_lstnew(f(l->content));
		if (newl->next == NULL)
			ft_lstclear(&lst, del);
		newl = newl->next;
	}
	return (new_start);
}
