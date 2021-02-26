/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/26 14:30:42 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool				same_key(char *key, t_list *envp)
{
	size_t	count;
	char	*tmp;

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

char				**turn_envp_into_strs(t_list *envp)
{
	size_t	index;
	char	**strs;

	index = 0;
	if (!(strs = malloc(sizeof(char *) * (ft_lstsize(envp) + 1))))
		return (NULL);
	while (envp)
	{
		strs[index] = ft_strdup((char*)envp->content);
		index++;
		envp = envp->next;
	}
	strs[index] = NULL;
	return (strs);
}

char				*get_key(char *argv)
{
	size_t	len;
	char	*key;

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

unsigned long long	ft_atoull(const char *str)
{
	size_t				index;
	unsigned long long	n;

	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+')
		index++;
	n = 0;
	while (ft_isdigit(str[index]))
	{
		n = n * 10 + (str[index] - '0');
		index++;
	}
	return (n);
}

long long			ft_atoll(const char *str)
{
	bool		sign;
	size_t		index;
	long long	n;

	index = 0;
	sign = false;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = true;
		index++;
	}
	n = ft_atoull(&str[index]);
	if (sign)
		return (-n);
	return (n);
}
