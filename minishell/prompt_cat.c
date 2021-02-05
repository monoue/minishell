/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_welcome_picture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:05:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/05 09:32:18 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_welcome_picture(void)
{
	ft_putendl("\n                                                     ");
	ft_putendl("                              ,                        ");
	ft_putendl("              ,-.       _,---._ __  / \\               ");
	ft_putendl("             /  )    .-'       `./ /   \\              ");
	ft_putendl("            (  (   ,'            `/    /|              ");
	ft_putendl("             \\  `-\"             \\'\\   / |          ");
	ft_putendl("              `.              ,  \\ \\ /  |            ");
	ft_putendl("\t       /`.          ,'-`----Y   |              ");
	ft_putendl("              (            ;        |   /              ");
	ft_putendl("              |  ,-.    ,-'         |  /               ");
	ft_putendl("              |  | (   |  minishell | /                ");
	ft_putendl("              )  |  \\  `.___________|/                ");
	ft_putendl("              `--'   `--'                              ");
	ft_putendl("           \033[0m\033[34mBIENVENUE DANS NOTRE MINISHELL\033[0m \033[31m❤️\033[0m\n   ");
}

void	put_farewell_picture(void)
{
	write(2, "\n", 1);
	ft_putendl_fd("            \033[5m*     \033[33m,MMM8&&&.            \033[0m*                            ", 2);
	ft_putendl_fd("                  \033[33mMMMM88&&&&&    \033[0m.                                  ", 2);
	ft_putendl_fd("                 \033[33mMMMM88&&&&&&&      \033[0m                                ", 2);
	ft_putendl_fd("     *          \033[33mMMM88&&&&&&&&&&                                      ", 2);
	ft_putendl_fd("                 MMM88&&&&&&&&                                      ", 2);
	ft_putendl_fd("                 'MMM88&&&&&&'                                      ", 2);
	ft_putendl_fd("                   'MMM8&&&'       \033[0m*                                 ", 2);
	ft_putendl_fd("          \033[30m|\\___/|                                                  ", 2);
	ft_putendl_fd("          \033[30m)     (              \033[0m.              '                      ", 2);
	ft_putendl_fd("         \033[30m=\\     /=                                                 ", 2);
	ft_putendl_fd("           \033[30m)===(        \033[0m*                                            ", 2);
	ft_putendl_fd("          \033[30m/     \\                                                  ", 2);
	ft_putendl_fd("          \033[30m|     |                                                   ", 2);
	ft_putendl_fd("         \033[30m/       \\                    ", 2);
	ft_putendl_fd("         \033[30m\\       / \033[34mAu revoir cher(e) visiteur(se)\033[0m                                        ", 2);
	ft_putendl_fd("  _/\\_/\\_/\033[30m\\__  _/\033[0m_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_  ", 2);
	ft_putendl_fd("  |  |  |  |\033[30m( (  \033[0m|  |  |  |  |  |  |  |  |  |  |  |                 ", 2);
	ft_putendl_fd("  |  |  |  | \033[30m) ) \033[0m|  |  |  |  |  |  |  |  |  |  |  |                 ", 2);
	ft_putendl_fd("  |  |  |  |\033[30m(_(  \033[0m|  |  |  |  |  |  |  |  |  |  |  |                  ", 2);
	ft_putendl_fd("  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                  ", 2);
	ft_putendl_fd("  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                  ", 2);
}
