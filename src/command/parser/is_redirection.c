/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:24:05 by monoue            #+#    #+#             */
<<<<<<< HEAD:minishell/command/parser/is_redirection.c
/*   Updated: 2021/01/27 11:33:10 by monoue           ###   ########.fr       */
=======
/*   Updated: 2021/01/28 07:01:15 by monoue           ###   ########.fr       */
>>>>>>> sabrina_tidy:minishell/parser/is_redirection.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection_char(char c)
{
	return (ft_strchr("><|", c));
}
