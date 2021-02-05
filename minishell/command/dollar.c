/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/05 17:40:19 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char     *skip_space_for_the_fucking_no_dblquo_dollar(char *value)
{
    int     i;
    int     j;
    char     *tmp;

    i = 0;
    j = 0;
    tmp = ft_strdup("");
    while (value[i])
    {
        if ((!is_space_or_tab(value[i])) || (is_space_or_tab(value[j + i - 1]) && !is_space_or_tab(value[j + i])))
        {
            tmp[j] = value[i];
            j++;
        }
        i++;
    }
    return (tmp);
}

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
    char    *value_tmp;
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
        value_tmp = ft_strdup("");
        if (flag != 2)
        {
            value_tmp = skip_space_for_the_fucking_no_dblquo_dollar(tmp_var);
            value = ft_strjoin(value, value_tmp);
        }
        else
            value = ft_strjoin(value, tmp_var);
        i++;
        free(tmp_var);
        free(value_tmp);
    }
    free(tmp);
    return (value);
}
