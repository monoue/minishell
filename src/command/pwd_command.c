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
	char	*buf;

	(void)argv;
	buf = getcwd(NULL, 1025);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	SAFE_FREE(buf);
}
