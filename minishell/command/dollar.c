/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:03:56 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_var(char *argv)
{
    int     i;
    int     cnt;
    char    *key;
    char    *tmp;

    cnt = ft_strlen(argv);
    key = malloc(cnt);
    i = 0;
    while (i + 1 < cnt)
    {
        key[i] = argv[i + 1];
        i++;
    }
    key[i] = '\0';
    tmp = ft_strjoin(key, "=");
    free(key);
    return (tmp);
}

char     *dollar(char *argv, t_list *envp)
{
    int     count;
    char    **tmp;
    char    *variable;
    char    *tmp_var;
    char    *value;
    int     i;
    t_list  *tmp_list;

    variable = NULL;
    tmp_var = ft_strdup("");
    value = ft_strdup("");
    i = 0;
    tmp = ft_split(argv, '$');
    while (tmp[i])
    {   
        tmp[i] = ft_strjoin(tmp[i], "=");
        tmp_list = envp;
        while (tmp_list && tmp_list->next)
        {
            if (ft_strncmp((char*)tmp_list->content, tmp[i], ft_strlen(tmp[i])) == 0)
                variable = ft_strdup((char*)tmp_list->content);
            tmp_list = tmp_list->next;
        }
        if (variable)
        {
            count = ft_strrchr_int(variable, '=');
            tmp_var = ft_substr(variable, count + 1, ft_strlen(variable) - count);
            free(variable);
        }
        value = ft_strjoin(value, tmp_var);
        i++;
        free(tmp_var);
    }
    free(tmp);
    return (value);
}
