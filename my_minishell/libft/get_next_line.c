/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:14:11 by monoue            #+#    #+#             */
/*   Updated: 2020/07/23 08:25:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_index_of_line_break(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (NOT_FOUND);
}

static int		free_both_and_return_error(char **fd_str, char *buff)
{
	free(fd_str);
	free(buff);
	return (ERROR);
}

static int		get_until_line_break(int fd, char **fd_str, int *br_index)
{
	char	*buff;
	char	*str_src;
	int		read_ret;

	if (!(buff = malloc(sizeof(*buff) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while ((read_ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[read_ret] = '\0';
		str_src = ft_strjoin(*fd_str, buff);
		free(*fd_str);
		if (!str_src)
			return (free_both_and_return_error(fd_str, buff));
		*fd_str = str_src;
		if ((*br_index = get_index_of_line_break(*fd_str)) != NOT_FOUND)
			break ;
	}
	if (read_ret == FILE_END)
		*br_index = get_index_of_line_break(*fd_str);
	SAFE_FREE(buff);
	if (read_ret > 0)
		return (NOT_EOF);
	return (read_ret);
}

/*
**  ---definitions---
**
**	MAX_FD		256
**	NOT_EOF		1
**	FILE_END	0
**	ERROR		-1
**	NOT_FOUND	-1
*/

int				get_next_line(int const fd, char **line)
{
	static char	*fd_arr[MAX_FD + 1];
	char		*arr_src;
	int			read_status;
	int			br_index;

	*line = NULL;
	if (fd > MAX_FD || fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!fd_arr[fd] && !(fd_arr[fd] = ft_strdup("")))
		return (ERROR);
	read_status = get_until_line_break(fd, &fd_arr[fd], &br_index);
	if (read_status == ERROR)
		return (ERROR);
	if (read_status == FILE_END && br_index == NOT_FOUND)
	{
		*line = ft_strdup(fd_arr[fd]);
		SAFE_FREE(fd_arr[fd]);
		return (*line ? FILE_END : ERROR);
	}
	*line = ft_substr(fd_arr[fd], 0, br_index);
	arr_src = ft_strdup(fd_arr[fd] + br_index + 1);
	free(fd_arr[fd]);
	fd_arr[fd] = arr_src;
	return ((fd_arr[fd] && *line) ? NOT_EOF : FILE_END);
}
