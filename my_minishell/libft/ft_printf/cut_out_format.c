/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_out_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:11:10 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 13:56:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cut_out_format.h"

static bool	isflag(const unsigned int c)
{
	if (is_of_chars(c, 4, '-', '0', '.', '*'))
		return (true);
	return (false);
}

char		*cut_out_format(const char **format, va_list *ap)
{
	char	*format_cut;

	format_cut = ft_strdup("%");
	(*format)++;
	while (isflag(**format) || ft_isdigit(**format))
	{
		if (**format == '*')
			format_cut = ft_strjoin_free_both(format_cut,
											ft_itoa(va_arg(*ap, int)));
		else
			format_cut = ft_strjoin_free_both(format_cut,
													ft_ctoa(**format));
		(*format)++;
	}
	if (isconversion_c(**format))
	{
		format_cut = ft_strjoin_free_both(format_cut,
													ft_ctoa(**format));
		(*format)++;
	}
	return (format_cut);
}
