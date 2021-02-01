/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 16:57:30 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 15:05:09 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "../libft.h"
#include "cut_out_format.h"
#include "defs.h"
#include "fill_with_zero.h"
#include "ft_xtoa_printf.h"
#include "init_format_info.h"
#include "is.h"
#include "put_result.h"
#include "set_zero_minwidth_minus_prec.h"

static bool				isvalid_format(char *format_cut)
{
	if (!format_cut || ft_strlen(format_cut) < 2)
		return (false);
	return (isconversion_c(format_cut[ft_strlen(format_cut) - 1]));
}

static char				*deal_with_null_case(char *str)
{
	if (!str)
		str = ft_strdup("(null)");
	return (str);
}

static void				*get_value(t_format_info *info, va_list *ap)
{
	unsigned int	c;

	if (ft_strchr("di", info->conv_c))
		return (ft_itoa((long)va_arg(*ap, int)));
	else if (info->conv_c == 'u')
		return (ft_utoa(va_arg(*ap, unsigned int)));
	else if (info->conv_c == 'x' || info->conv_c == 'X')
		return (ft_xtoa_printf((unsigned long long)va_arg(*ap, unsigned int),
																info->conv_c));
	else if (info->conv_c == 'p')
		return (ft_xtoa_printf((unsigned long long)va_arg(*ap, void *),
																info->conv_c));
	else if (info->conv_c == 'c')
	{
		if ((c = va_arg(*ap, unsigned int)) != 0)
			return (ft_ctoa(c));
		info->c_null = true;
		return (ft_ctoa('1'));
	}
	else if (info->conv_c == '%')
		return (ft_ctoa('%'));
	else if (info->conv_c == 's')
		return (deal_with_null_case(ft_strdup(va_arg(*ap, char *))));
	return (NULL);
}

static t_format_info	*get_format_info(char *target, va_list *ap)
{
	int				index;
	t_format_info	*info;

	info = malloc(sizeof(t_format_info) * 1);
	if (!info)
		return (NULL);
	init_format_info(info);
	info->conv_c = target[ft_strlen(target) - 1];
	index = 1;
	while (!isconversion_c(target[index]))
		set_zero_minwidth_minus_prec(target, &index, info);
	info->value = get_value(info, ap);
	return (info);
}

int						ft_printf(const char *format, ...)
{
	size_t	count;
	char	*format_cut;
	va_list	ap;

	va_start(ap, format);
	count = 0;
	while (format && *format)
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			format++;
			count++;
		}
		else
		{
			format_cut = cut_out_format(&format, &ap);
			if (isvalid_format(format_cut))
				count += put_result(get_format_info(format_cut, &ap));
			SAFE_FREE(format_cut);
		}
	}
	va_end(ap);
	return (count);
}
