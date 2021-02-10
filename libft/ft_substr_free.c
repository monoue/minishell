/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:21:27 by monoue            #+#    #+#             */
/*   Updated: 2021/02/10 11:46:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_free(char *original_s, unsigned int start_index, size_t len)
{
	char *tmp;

	tmp = original_s;
	original_s = ft_substr(original_s, start_index, len);
	free(tmp);
	return (original_s);
}
