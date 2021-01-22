/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/01/22 15:17:23 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <sys/wait.h>

# define ERR_MSG		"error: "
# define FATAL_ERR_MSG	ERR_MSG"fatal\n"

typedef			enum
{
	TYPE_END,
	TYPE_PIPE,
	TYPE_BREAK,

	TYPES_NUM
}				t_type;

typedef struct	s_chunk
{
	char			**argv;
	size_t			size;
	t_type			type;
	int				fds[2];

	struct s_chunk	*prev;
	struct s_chunk	*next;
}				t_chunk;

#endif
