/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:49 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/26 17:49:11 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir("/") == ERROR)
			perror("");
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			perror("");
	}
	return (1);
}
