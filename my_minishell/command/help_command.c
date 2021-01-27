/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/27 11:32:42 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*builtin_str1[] = {
// 	"cd",
// 	"help",
// 	"exit",
// 	"echo",
// 	"export",
// 	"unset",
// 	"exit",
// 	"env",
// };

// int	num_builtins1()
// {
// 	return (sizeof(builtin_str1) / sizeof(char *));
// }

// int	help()
// {
	
// 	int	i;

// 	// printf("Type program names and arguments, and hit enter.\n");
// 	// printf("The following are built in: \n");
// 	ft_putstr("Type program names and arguments, and hit enter.\n");
// 	ft_putstr("The following are built in: \n");
// 	i = 0;	
// 	while (i < num_builtins1())
// 	{
// 		ft_putstr(builtin_str1[i]);
// 		ft_putstr("\n");
// 		i++;
// 	}
// 	return (1);
// }

const char *g_builtin_cmds[] = {
	"cd",
	"help",
	"exit",
	"echo",
	"export",
	"unset",
	"exit",
	"env",
	NULL
};

int	help(void) // return value, void でも OK?
{
	size_t	index;

	ft_putstr("Type program names and arguments, and hit enter.\n");
	ft_putstr("The following are built in: \n");
	index = 0;
	while (g_builtin_cmds[index])
	{
		ft_putendl(g_builtin_cmds[index]);
		index++;
	}
	return (1); // unnecessary?
}
