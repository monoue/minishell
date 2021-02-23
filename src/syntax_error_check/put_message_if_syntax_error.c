/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message_if_syntax_error.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:49:32 by monoue            #+#    #+#             */
/*   Updated: 2021/02/23 14:38:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_syntax_error_message(char **words, int ret)
{
	ft_putstr_err("-bash: syntax error near unexpected token `");
	if (words[ret])
		ft_putstr_err(words[ret]);
	else
		ft_putstr_err("newline");
	ft_putstr_err("`\n");
}

bool		put_message_if_syntax_error(char *command_line, t_list *envp)
{
	char	**words;
	int		ret;

	words = split_command_line(command_line, envp);
	ret = check_syntax(command_line, words);
	if (ret == SYNTAX_QUOTED_WRONGLY || ret == SYNTAX_VALID)
		ft_free_split(words);
	if (ret == SYNTAX_QUOTED_WRONGLY)
	{
		g_last_exit_status = EXIT_FAILURE;
		ft_putstr_err("-bash: quotes not closed\n");
		return (true);
	}
	if (ret != SYNTAX_VALID)
	{
		g_last_exit_status = SYNTAX_ERROR;
		put_syntax_error_message(words, ret);
		ft_free_split(words);
		return (true);
	}
	return (false);
}
