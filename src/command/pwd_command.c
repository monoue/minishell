/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:21 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 19:40:26 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pwd(char **argv)
{
	char	buf[MAX_INPUT + 1];

	(void)argv;
	getcwd(buf, MAX_INPUT);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
}
