/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:57 by monoue            #+#    #+#             */
/*   Updated: 2021/02/10 16:34:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo) //"ctrl-C"
{
	(void)signo;
	if (pid != 0)
	{
		kill(pid, SIGINT);
		pid = 0;
	}
	else
	{
		ft_putstr_fd("\b \b\b \n", 2);
		ft_putstr_fd(PROMPT, 2);
	}
}

void 	quit_signal(int signo) //"ctrl-\"
{
	(void)signo;
	if (pid != 0)
	{
		kill(pid, SIGQUIT);
		ft_putstr_fd("Quit: 3", 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);

}

int 	main(void)
{
	char		*line;
	extern char	**environ;
	t_list		*envp;
	t_list		*tmp;
	int			rv;
	
	put_welcome_picture();
	envp = ft_lstnew(*environ);
    environ++;
    while(*environ)
    {
        tmp = ft_lstnew(*environ);
        ft_lstadd_back(&envp, tmp);
        environ++;
    }
	rv = 1;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, quit_signal);
	while (42)
	{
		ft_putstr(PROMPT);
		rv = get_next_line(STDIN_FILENO, &line);
		if (rv == ERROR)
			exit_err_msg(MALLOC_ERR);
		if (rv == 0)
			return (0 * write(1, "exit(ctrl-D)\n", 14));
		if (str_is_of_spaces(line) || put_message_if_syntax_error(line))
			continue ;
		// if (is_invalid_syntax(line)) // 未完成
		// {
		// 	SAFE_FREE(line);
		// 	exit(EXIT_FAILURE);
		// }
		// 環境変数をここで整える
		// コメントもここで削る
		process_command_line(line, envp);
	}
	return (EXIT_SUCCESS);
}
