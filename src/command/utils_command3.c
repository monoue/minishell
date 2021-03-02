/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:14:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/02 08:17:58 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				add_variable(char *argv, t_list *envp)
{
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

int					ft_strrchr_int(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len--)
		if (*(s + len) == c)
			return (len);
	return (0);
}

char				*ft_strcat(char *dest, char *src)
{
	int	d_length;
	int	i;

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

bool				is_dollar(char c)
{
	return (c == '$');
}

bool				has_dollar_variable(char *arg)
{
	const size_t	len = ft_strlen(arg);
	size_t			index;

	if (!arg)
		return (false);
	index = 0;
	while (index < len)
	{
		if (is_specific_char_not_escaped(arg, index, is_dollar)
															&& index + 1 < len)
		{
			return (true);
		}
		index++;
	}
	return (false);
}
