/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:11:03 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:39:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const size_t	h_len = ft_strlen(haystack);
	const size_t	n_len = ft_strlen(needle);
	size_t			index;

	if (haystack == NULL || needle == NULL || n_len > h_len)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	index = 0;
	while (index + n_len <= h_len)
	{
		if (ft_strncmp(&haystack[index], needle, n_len) == 0)
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
