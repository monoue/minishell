/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/01/25 13:44:12 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "debug.h"

# include <sys/wait.h>

# define ERR_MSG		"error: "
# define FATAL_ERR_MSG	ERR_MSG"fatal\n"
# define MALLOC_ERR "memory allocation error\n"

__BEGIN_DECLS
extern int * __error(void);
#define errno (*__errosr())
__END_DECLS

typedef			enum
{
	TYPE_END,
	TYPE_PIPE,
	TYPE_BREAK,
	TYPE_READ,
	TYPE_WRITE,
	TYPE_APPEND,

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

char			**split_cmd_line(char const *str);
void			pwd(t_chunk *chunk);
int				help();
int				minishell_exit();
int				cd(char **args);
void			wc(char *fullpath_cmd, t_chunk *chunk, char **environ);
void			echo(t_chunk *chunk);
void			env(char **environ);
void			export(t_chunk *chunk, char **environ);

#endif
