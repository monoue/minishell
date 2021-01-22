/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:11:03 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:17:37 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			index;
	const size_t	n_len = ft_strlen(needle);
	const size_t	range_to_check = MIN(len, ft_strlen(haystack));

	if (haystack == NULL || needle == NULL)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (n_len > range_to_check)
		return (NULL);
	index = 0;
	while (index + n_len <= range_to_check)
	{
		if (ft_strncmp(&haystack[index], needle, n_len) == 0)
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
