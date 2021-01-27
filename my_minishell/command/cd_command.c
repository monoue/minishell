/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:49 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/27 11:33:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// can be void?
int	cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir("/") == ERROR) // 違う。
			perror("");
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			perror("");
	}
	return (1); // unnecessary?
}
