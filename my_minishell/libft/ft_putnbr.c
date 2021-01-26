/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:23:14 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 10:08:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == INT_MIN)
	{
		write(STDOUT_FILENO, INT_MIN_STR, ft_strlen(INT_MIN_STR));
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
		return ;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(ITOC(n % 10));
}
