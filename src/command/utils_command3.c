/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:14:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/08 11:21:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_variable(char *argv, t_list *envp)
{
	//t_list *new;
	//char *tmp;

	//tmp  = ft_strdup(argv);
	//new = ft_lstnew(tmp);
	//ft_lstadd_back(&envp, new);
	t_list	*new;
	t_list	*tmp;

	new = malloc(sizeof(t_list));
	new->content = ft_strdup(argv);
	while (envp && envp->next && envp->next->next)
		envp = envp->next;
	tmp = envp->next;
	envp->next = new;
	new->next = tmp;
}

int		ft_strrchr_int(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len--)
		if (*(s + len) == c)
			return (len);
	return (0);
}

char    *ft_strcat(char *dest, char *src)
{
    int d_length;
    int i;

    d_length = 0;
    while (dest[d_length])
        d_length++;
    i = 0;
    while (src[i])
    {
        dest[d_length] = src[i];
        i++;
        d_length++;
    }
    dest[d_length] = '\0';
    return (dest);
}

int         dollar_or_not(char *arg, int c)
{
    size_t	i;
    size_t	j;

    i = 0;
    j = 0;
    while (arg[i])
    {
        if (arg[i] == c)
            j++;
        i++;
    }
    if (0 < j && j < i)
        return (1);
    return (0);
}
