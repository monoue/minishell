/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:16:21 by monoue            #+#    #+#             */
/*   Updated: 2021/02/08 10:11:54 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *src, void *(*f)(void *), void (*del)(void *))
{
	t_list	*src_copy;
	t_list	*dst;
	t_list	*tmp;

	if (!src || !f)
		return (NULL);
	dst = ft_lstnew(f(src->content));
	if (!dst)
		return (NULL);
	src_copy = src->next;
	while (src_copy)
	{
		tmp = ft_lstnew(f(src_copy->content));
		if (!tmp)
		{
			ft_lstclear(&dst, del);
			return (NULL);
		}
		ft_lstadd_back(&dst, tmp);
		src_copy = src_copy->next;
	}
	return (dst);
}
