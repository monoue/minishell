/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:01:15 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:00:12 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is.h"

bool	is_of_chars(const unsigned int c, int argc, ...)
{
	va_list	ap;

	va_start(ap, argc);
	while (argc--)
	{
		if (va_arg(ap, unsigned int) == c)
		{
			va_end(ap);
			return (true);
		}
	}
	va_end(ap);
	return (false);
}

bool	isconversion_c(const unsigned int c)
{
	if (is_of_chars(c, 9, 'c', 'd', 'i', 'x', 'X', 's', 'u', 'p', '%'))
		return (true);
	return (false);
}
