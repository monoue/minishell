/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 07:20:40 by monoue            #+#    #+#             */
/*   Updated: 2020/10/22 10:32:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ctoa(char c)
{
	char	*c_as_str;

	c_as_str = ft_strdup("0");
	if (c_as_str == NULL)
		return (NULL);
	c_as_str[0] = c;
	return (c_as_str);
}
