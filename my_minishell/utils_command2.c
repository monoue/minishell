/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/01/26 19:12:27 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		same_key(char *key, t_list *envp)
{
	int	count;

	count = ft_strlen(key);
	while (envp)
	{
		if (ft_strncmp(envp->content, key, count) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

char    *check_key(char **argv)
{
    int     i;
    int     count;
    char    *key;


    count = 0;
    while (ft_strcmp(argv[count], "=") != 0)
        count++;
    count++;
    key = malloc(count + 1);
    i = 0;
    while (i < count)
    {
        key[i] = *argv[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

void	*delete_variable(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}