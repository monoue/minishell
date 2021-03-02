/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/03 08:40:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *argv)
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
