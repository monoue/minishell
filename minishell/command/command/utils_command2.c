/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/27 11:32:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int		same_key(char *key, t_list *envp)
// {
// 	int	count;

// 	count = ft_strlen(key);
// 	while (envp)
// 	{
// 		if (ft_strncmp(envp->content, key, count) == 0)
// 			return (1);
// 		envp = envp->next;
// 	}
// 	return (0);
// }

bool	is_key_duplicated(char *key, t_list *envp)
{
	while (envp)
	{
		if (ft_strequal(envp->content, key))
			return (true);
		envp = envp->next;
	}
	return (false);
}

// char    *check_key(char **argv)
// {
//     int     i;
//     int     count;
//     char    *key;


//     count = 0;
//     while (ft_strcmp(argv[count], "=") != 0)
//         count++;
//     count++;
//     key = malloc(count + 1);
//     i = 0;
//     while (i < count)
//     {
//         key[i] = *argv[i];
//         i++;
//     }
//     key[i] = '\0';
//     return (key);
// }

char    *check_key(char **argv)
{
    size_t	index;
    size_t	count;
    char    *key;

    count = 0;
    while (!ft_strequal(argv[count], "="))
        count++;
    count++;
    key = ft_calloc(count + 1, sizeof(char));
	if (!key)
		return (NULL);
	return (ft_strncpy(key, *argv, count));
}

// void	*delete_variable(void *ptr)
// {
// 	if (ptr)
// 	{
// 		free(ptr);
// 		ptr = NULL;
// 	}
// 	return (NULL);
// }

void	*delete_variable(void *ptr)
{
	if (ptr)
		SAFE_FREE(ptr);
	return (NULL);
}
