/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
<<<<<<< HEAD:minishell/command/command/unset_command.c
/*   Updated: 2021/01/27 11:32:48 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/command/unset_command.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
<<<<<<< HEAD:minishell/command/command/unset_command.c

// void	unset(t_chunk *chunk, t_list *envp)
// {
// 	int		i;
// 	int		count;
// 	char	*key;
// 	char	*new;
// 	char	*tmp;

// 	i = 1;
// 	while (chunk->argv[i])
// 	{
// 		count = ft_strlen(chunk->argv[i]);
// 		if (same_key(chunk->argv[i], envp) == 1)
// 		{
// 			while (envp && envp->next)
// 			{
// 				tmp = envp->content;
// 				if (ft_strncmp(tmp, chunk->argv[i], count) == 0)
// 				{
// 					delete_variable(envp->content);
// 				}
// 				envp = envp->next;
// 			}
// 		}
// 		i++;
// 	}
// }
=======
>>>>>>> sabrina_tidy:minishell/command/unset_command.c

void	unset(t_chunk *chunk, t_list *envp)
{
	size_t	index;
	char	*key;
	char	*new;
	char	*tmp;

	index = 1;
	while (chunk->argv[index])
	{
		if (is_key_duplicated(chunk->argv[index], envp))
		{
			while (envp && envp->next)
			{
				tmp = envp->content;
				if (ft_strequal(tmp, chunk->argv[index]))
					delete_variable(envp->content);
				envp = envp->next;
			}
		}
		index++;
	}
}
