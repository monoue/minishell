/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/09 15:44:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	same_key(char *key, t_list *envp)
{
	size_t	count;
    char    *tmp;

	count = ft_strlen(key);
	while (envp)
	{
        tmp = envp->content;
		if (ft_strnequal(tmp, key, count))
			return (true);
		envp = envp->next;
	}
	return (false);
}

char        **turn_envp_into_strs(t_list *envp)
{
    size_t	index;
    char    **strs;
    // char    *tmp;

    index = 0;
   	if (!(strs = malloc(sizeof(char *) * (ft_lstsize(envp) + 1))))
		return (NULL);
    while (envp)
    {
        // tmp = envp->content;
        // array[i] = ft_strdup(tmp);
        strs[index] = ft_strdup((char*)envp->content);
        index++;
        envp = envp->next;
    }
    strs[index] = NULL;
    return (strs);
}

// char		*if_same_key_char(char *key, t_list *envp)
// {
// 	int	    count;
//     char    *tmp;
//     char    *value;

// 	count = ft_strlen(key);
// 	while (envp && envp->next)
// 	{
//         tmp = envp->content;
// 		if (ft_strncmp(tmp, key, count) == 0)
//         {
//             value = ft_strdup((char*)envp->content);
// 			return (value);
//         }
// 		envp = envp->next;
// 	}
// 	return (NULL);
// }

char    *get_key(char *argv)
{
    size_t	len;
    char    *key;

    len = 0;
    while (argv[len])
    {
        if (argv[len] == '=')
		{
			len++;
            break ;
		}
        len++;
    }
	key = ft_strndup(argv, len);
	if (!key)
		exit_err_msg(MALLOC_ERR);
    return (key);
}
