/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_both.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:37:04 by monoue            #+#    #+#             */
/*   Updated: 2020/10/15 16:08:29 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	const char	*joined_str = ft_strjoin(s1, s2);

	SAFE_FREE(s1);
	SAFE_FREE(s2);
	return ((char *)joined_str);
}
