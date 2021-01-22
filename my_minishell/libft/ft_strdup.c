/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:32:49 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 13:01:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *original_s)
{
	size_t	len;
	char	*dup_s;

	len = ft_strlen(original_s);
	dup_s = malloc(sizeof(char) * (len + 1));
	if (!dup_s)
		return (NULL);
	return (ft_strcpy(dup_s, original_s));
}
