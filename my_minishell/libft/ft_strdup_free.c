/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:32:49 by monoue            #+#    #+#             */
/*   Updated: 2020/10/15 15:09:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_free(char *original_s)
{
	const char	*duplicated_s = ft_strdup(original_s);

	SAFE_FREE(original_s);
	return ((char *)duplicated_s);
}
