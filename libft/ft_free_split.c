/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 06:46:58 by monoue            #+#    #+#             */
/*   Updated: 2021/03/11 10:57:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **strs)
{
	size_t	index;

	if (!strs)
		return ;
	index = 0;
	while (strs[index])
	{
		SAFE_FREE(strs[index]);
		index++;
	}
	SAFE_FREE(strs);
}
