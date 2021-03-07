/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:33:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/05 18:19:34 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *argv)
{
	size_t	len;
	char	*key;
	char	*tmp_key;

	len = 0;
	g_plus = 0;
	while (argv[len])
	{
		if (argv[len] == '+' && argv[len + 1])
			g_plus = 1;
		if (argv[len] == '=')
		{
			len++;
			break ;
		}
		len++;
	}
	tmp_key = ft_strndup(argv, len);	
	if (!tmp_key)
		exit_err_msg(MALLOC_ERR);
	key = skip_plus(tmp_key);
	SAFE_FREE(tmp_key);
	return (key);
}
