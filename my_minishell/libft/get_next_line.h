/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:05:47 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 12:26:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define MAX_FD			256
# define NOT_EOF		1
# define FILE_END		0
# define NOT_FOUND		-1
# define BUFFER_SIZE	1024

int		get_next_line(int fd, char **line);

#endif
