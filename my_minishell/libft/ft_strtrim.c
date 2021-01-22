/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:09:52 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:21:58 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	start_index;
	size_t	end_index;
	size_t	s_len;

	if (str == NULL || set == NULL)
		return (NULL);
	s_len = ft_strlen(str);
	start_index = 0;
	while (start_index < s_len && ft_strchr(set, str[start_index]))
		start_index++;
	end_index = (size_t)s_len;
	while (end_index > start_index && ft_strchr(set, str[end_index - 1]))
		end_index--;
	return (ft_substr((char *)str, start_index, end_index - start_index));
}
