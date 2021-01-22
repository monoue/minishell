/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_result.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:26:28 by monoue            #+#    #+#             */
/*   Updated: 2021/01/20 16:28:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_RESULT_H
# define PUT_RESULT_H

# include "../libft.h"
# include "fill_with_zero.h"
# include "apply_margin.h"

int	put_result(t_format_info *info);
int	put_result_fd(t_format_info *info, int fd);

#endif
