/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/26 16:35:43 by monoue           ###   ########.fr       */
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
    int           i;

    envp = NULL;
    i = 0;
    if (environ[0] == NULL)
    {
        tmp = new_env("SHLVL=1");
        ft_lstadd_back(&envp, tmp);
        tmp = new_env("_=./minishell");
        ft_lstadd_back(&envp, tmp);
        return (envp);
    }
    index = 0;
    while (environ[index])
    {
        if (ft_strncmp(environ[index], "_=", 2) == 0)
            i = 1;
        index++;
    }
    if (environ[0])
        envp = new_env(environ[0]);
    if (i == 0)
    {
        tmp = new_env("_=./minishell");
        ft_lstadd_back(&envp, tmp);
    }
    index = 1;
    while (environ[index])
    {
        tmp = new_env(environ[index]);
        ft_lstadd_back(&envp, tmp);
        index++;
    }
    return (envp);
}