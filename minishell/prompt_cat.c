/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_cat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:05:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/03 14:08:33 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cat_exit(void)
{
	write(1, "\n", 1);
	ft_putendl_fd("            \033[5m*     \033[33m,MMM8&&&.            \033[0m*                            ", 2);
	ft_putendl_fd("                  \033[33mMMMM88&&&&&    \033[0m.                                  ", 2);
	ft_putendl_fd("                 \033[33mMMMM88&&&&&&&      \033[0m                                ", 2);
	ft_putendl_fd("     *          \033[33mMMM88&&&&&&&&                                      ", 2);
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


void	prompt_cat(void)
{
	ft_putendl_fd("\n                                                     ", 1);
	ft_putendl_fd("	                             ,                        ", 1);
	ft_putendl_fd("              ,-.       _,---._ __  / \\               ", 1);
	ft_putendl_fd("             /  )    .-'       `./ /   \\              ", 1);
	ft_putendl_fd("            (  (   ,'            `/    /|              ", 1);
	ft_putendl_fd("             \\  `-\"             \\'\\   / |          ", 1);
	ft_putendl_fd("              `.              ,  \\ \\ /  |            ", 1);
	ft_putendl_fd("              /`.          ,'-`----Y    |              ", 1);
	ft_putendl_fd("              (            ;        |   '              ", 1);
	ft_putendl_fd("              |  ,-.    ,-'         |  /               ", 1);
	ft_putendl_fd("              |  | (   |  minishell | /                ", 1);
	ft_putendl_fd("              )  |  \\  `.___________|/                ", 1);
	ft_putendl_fd("              `--'   `--'                              ", 1);
	ft_putendl_fd("           \033[0m\033[34mBIENVENUE DANS NOTRE MINISHELL\033[0m \033[31m❤️\033[0m\n   ", 1);
}