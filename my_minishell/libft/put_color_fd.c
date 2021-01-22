/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:58:09 by monoue            #+#    #+#             */
/*   Updated: 2021/01/22 17:50:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_color_fd(const char *str, t_colors color, int fd)
{
	const char *color_strs[COLORS_NUM] = {
		RED_S,
		GREEN_S,
		YELLOW_S,
		BLUE_S,
		PURPLE_S,
		CYAN_S
	};

	ft_putstr_fd((char *)color_strs[color], fd);
	ft_putstr_fd((char *)str, fd);
	ft_putstr_fd(RESET, fd);
}
