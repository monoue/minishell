/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:40:49 by sperrin           #+#    #+#             */
<<<<<<< HEAD:minishell/command/command/cd_command.c
/*   Updated: 2021/01/27 11:33:47 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/command/cd_command.c
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
