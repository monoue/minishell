/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:16:21 by monoue            #+#    #+#             */
/*   Updated: 2021/02/08 09:06:14 by monoue           ###   ########.fr       */
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
	newl = ft_lstnew(f(lst->content));
	if (!newl)
		return (NULL);
	new_start = newl;

	// l = lst;
	// new_start = newl;
	// while (l->next)
	// {
	// 	l = l->next;
	// 	newl->next = ft_lstnew(f(l->content));
	// 	if (newl->next == NULL)
	// 		ft_lstclear(&lst, del);
	// 	newl = newl->next;
	// }
	// return (new_start);
	t_list	*tmp;
	l = lst->next;
	while (l)
	{
		tmp = ft_lstnew(f(l->content));
		// if (!tmp)
		ft_lstadd_back(newl, tmp);
		// newl->next = ft_lstnew(f(l->content));
		// if (newl->next == NULL)
		// 	ft_lstclear(&lst, del);
		// newl = newl->next;
		l = l->next;
	}
	return (new_start);
}
