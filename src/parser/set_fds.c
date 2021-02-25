/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:45:12 by monoue            #+#    #+#             */
/*   Updated: 2021/02/25 09:17:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// これだと、僕の元のヤツと同様。
// つまり、ls hoge 2> file1 で、ls の出力がどこかに行く
// void	set_fds(t_fd *fds)
// {
// 	fds->input = STDIN_FILENO;
// 	fds->output = STDOUT_FILENO;
// }


/*
** duplicates original stdin and stdout fds
*/

// こうすることで、ls hoge 2> file1 で、ls の出力はちゃんと表示されるようになる。
void	set_fds(t_fd *fds)
{
	fds->input = dup(STDIN_FILENO);
	fds->output = dup(STDOUT_FILENO);
}
