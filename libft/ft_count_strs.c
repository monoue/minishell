/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 10:26:29 by monoue            #+#    #+#             */
/*   Updated: 2021/02/05 17:45:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_strs(const char **strs)
{
	size_t	count;

	if (!strs)
		return (0);
	count = 0;
	while (strs[count] != NULL)
		count++;
	return (count);
}
