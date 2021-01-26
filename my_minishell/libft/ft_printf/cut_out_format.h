/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_out_format.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:55:27 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:04:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUT_OUT_FORMAT_H
# define CUT_OUT_FORMAT_H

# include <stdarg.h>

# include "../libft.h"
# include "is.h"

char			*cut_out_format(const char **format, va_list *ap);

#endif
