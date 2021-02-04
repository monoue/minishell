/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:06:10 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		same_key(char *key, t_list *envp)
{
	int	    count;
    char    *tmp;

	count = ft_strlen(key);
	while (envp && envp->next)
	{
        tmp = envp->content;
		if (ft_strncmp(tmp, key, count) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

int		get_content(char *key, t_list *envp)
{
	int	    count;
    int     i;
    char    *tmp;

    i = 0;
	count = ft_strlen(key);
	while (envp && envp->next)
	{
        tmp = envp->content;
		if (ft_strncmp(tmp, key, count) == 0)
			return (i - 1);
		envp = envp->next;
        i++;
	}
	return (i);
}

char        **struct_to_array(t_list *envp)
{
    int     i;
    char    **array;
    char    *tmp;

    i = 0;
   	if (!(array = malloc(sizeof(char *) * (ft_lstsize(envp) + 1))))
		return (NULL);
    while (envp)
    {
        tmp = envp->content;
        array[i] = ft_strdup(tmp);
        i ++;
        envp = envp->next;
    }
    array[i] = NULL;
    return (array);
}

char		*if_same_key_char(char *key, t_list *envp)
{
	int	    count;
    char    *tmp;
    char    *value;

	count = ft_strlen(key);
	while (envp && envp->next)
	{
        tmp = envp->content;
		if (ft_strncmp(tmp, key, count) == 0)
        {
            value = ft_strdup((char*)envp->content);
			return (value);
        }
		envp = envp->next;
	}
	return (NULL);
}

char    *check_key(char *argv)
{
    int     i;
    int     cnt;
    char    *key;
    char    *tmp;

    cnt = 0;
    while (argv[cnt] != '\0')
    {
        if (argv[cnt] == '=')
            break;
        cnt++;
    }
    key = malloc(cnt + 1);
    i = 0;
    while (i < cnt)
    {
        key[i] = argv[i];
        i++;
    }
    key[i] = '\0';
    tmp = ft_strjoin(key, "=");
    free(key);
    return (tmp);
}
