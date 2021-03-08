/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_greeting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:05:27 by sperrin           #+#    #+#             */
/*   Updated: 2021/03/08 16:37:41 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		put_welcome_greeting(void)
{
	ft_putendl_err("\n");
	ft_putendl_err("                              ,");
	ft_putendl_err("              ,-.       _,---._ __  / \\");
	ft_putendl_err("             /  )    .-'       `./ /   \\");
	ft_putendl_err("            (  (   ,'            `/    /|");
	ft_putendl_err("             \\  `-\"             \\'\\   / |");
	ft_putendl_err("              `.              ,  \\ \\ /  |");
	ft_putendl_err("\t       /`.          ,'-`----Y   |");
	ft_putendl_err("              (            ;        |   /");
	ft_putendl_err("              |  ,-.    ,-'         |  /");
	ft_putendl_err("              |  | (   |  minishell | /");
	ft_putendl_err("              )  |  \\  `.___________|/");
	ft_putendl_err("              `--'   `--'");
	ft_putstr_err("           \033[0m\033[34mBIENVENUE DANS NOTRE MINISHELL");
	ft_putendl_err("\033\[0m \033[31m❤️\033[0m\n   ");
}

static void	put_cat(void)
{
	ft_putendl_err("          |\\___/|");
	ft_putendl_err("          )     (\t      \033[0m.\t      '");
	ft_putendl_err("         =\\     /=");
	ft_putendl_err("           )===(        \033[0m*");
	ft_putendl_err("          /     \\");
	ft_putendl_err("          |     |");
	ft_putendl_err("         /       \\");
	ft_putstr_err("         \\       / \033[34m");
	ft_putendl_err("Au revoir cher(e) visiteur(se)\033[0m");
	ft_putstr_err("  _/\\_/\\_/\\__  _/");
	ft_putendl_err("_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_  ");
	ft_putstr_err("  |  |  |  |( (  ");
	ft_putendl_err("|  |  |  |  |  |  |  |  |  |  |  |");
	ft_putstr_err("  |  |  |  | ) ) ");
	ft_putendl_err("|  |  |  |  |  |  |  |  |  |  |  |");
	ft_putstr_err("  |  |  |  |(_(  ");
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
