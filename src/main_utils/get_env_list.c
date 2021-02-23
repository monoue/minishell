/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/24 08:01:59 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list    *new_env(char *cont)
{
    t_list    *new;

    new = malloc(sizeof(t_list));
    if (!new)
        exit_err_msg(MALLOC_ERR);
    new->content = ft_strdup(cont);
    new->next = NULL;
    return (new);
}

t_list    *get_env_list(void)
{
    extern char    **environ;
    t_list        *envp;
    t_list        *tmp;
    size_t        index;

    if (!environ)
        return (NULL);
    // envp = malloc(sizeof(t_list));
	if (environ[0])
		envp = new_env(environ[0]);
    if (!envp)
        exit_err_msg(MALLOC_ERR);
    index = 1;
    while (environ[index])
    {
        tmp = new_env(environ[index]);
        ft_lstadd_back(&envp, tmp);
        index++;
    }
    return (envp);
}