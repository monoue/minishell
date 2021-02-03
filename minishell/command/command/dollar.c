/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/03 10:41:33 by sperrin          ###   ########.fr       */
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

char     *dollar(char **argv, t_list *envp)
{
    int     count;
    char    *tmp;
    char    *variable;
    char    *value;

    variable = NULL;
    tmp = get_var(argv[1]);
	while (envp && envp->next)
	{
		if (ft_strncmp((char*)envp->content, tmp, ft_strlen(tmp)) == 0)
            variable = ft_strdup((char*)envp->content);
		envp = envp->next;
	}
    if (variable)
    {
        count = ft_strrchr_int(variable, '=');
        value = ft_substr(variable, count + 1, ft_strlen(variable) - count);
        free(variable);
        return (value);
    }
    free(variable);
    return (NULL);
}
