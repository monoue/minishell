/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_greeting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:05:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/24 14:34:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		put_welcome_greeting(void)
{
	ft_putendl("\n");
	ft_putendl("                              ,");
	ft_putendl("              ,-.       _,---._ __  / \\");
	ft_putendl("             /  )    .-'       `./ /   \\");
	ft_putendl("            (  (   ,'            `/    /|");
	ft_putendl("             \\  `-\"             \\'\\   / |");
	ft_putendl("              `.              ,  \\ \\ /  |");
	ft_putendl("\t       /`.          ,'-`----Y   |");
	ft_putendl("              (            ;        |   /");
	ft_putendl("              |  ,-.    ,-'         |  /");
	ft_putendl("              |  | (   |  minishell | /");
	ft_putendl("              )  |  \\  `.___________|/");
	ft_putendl("              `--'   `--'");
	ft_putstr("           \033[0m\033[34mBIENVENUE DANS NOTRE MINISHELL");
	ft_putendl("\033\[0m \033[31m❤️\033[0m\n   ");
}

static void	put_cat(void)
{
	ft_putendl_err("          \033[30m|\\___/|");
	ft_putendl_err("          \033[30m)     (\t      \033[0m.\t      '");
	ft_putendl_err("         \033[30m=\\     /=");
	ft_putendl_err("           \033[30m)===(        \033[0m*");
	ft_putendl_err("          \033[30m/     \\");
	ft_putendl_err("          \033[30m|     |");
	ft_putendl_err("         \033[30m/       \\");
	ft_putstr_err("         \033[30m\\       / \033[34m");
	ft_putendl_err("Au revoir cher(e) visiteur(se)\033[0m");
	ft_putstr_err("  _/\\_/\\_/\033[30m\\__  _/\033[0m");
	ft_putendl_err("_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_  ");
	ft_putstr_err("  |  |  |  |\033[30m( (  \033[0m");
	ft_putendl_err("|  |  |  |  |  |  |  |  |  |  |  |");
	ft_putstr_err("  |  |  |  | \033[30m) ) \033[0m");
	ft_putendl_err("|  |  |  |  |  |  |  |  |  |  |  |");
	ft_putstr_err("  |  |  |  |\033[30m(_(  \033[0m");
	ft_putendl_err("|  |  |  |  |  |  |  |  |  |  |  |");
	ft_putendl_err("  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |");
	ft_putendl_err("  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |");
}

void		put_farewell_greeting(void)
{
	ft_putendl_err("    ");
	ft_putendl_err("             \033[5m*     \033[33m,MMM8&&&.\t    \033[0m*");
	ft_putendl_err(" \t\t \033[33mMMMM88&&&&&    \033[0m.");
	ft_putendl_err("                 \033[33mMMMM88&&&&&&&      \033[0m");
	ft_putendl_err("     *          \033[33mMMM88&&&&&&&&&&");
	ft_putendl_err("                 MMM88&&&&&&&&");
	ft_putendl_err("                 'MMM88&&&&&&'");
	ft_putendl_err("                   'MMM8&&&'       \033[0m*");
	put_cat();
}
