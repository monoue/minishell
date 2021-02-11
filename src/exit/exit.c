#include "minishell.h"

void	exit_err_msg(char *err_msg)
{
	ft_putstr_err(err_msg);
	exit(EXIT_FAILURE);
}

void	exit_bash_err_msg(const char *error_factor, const char *error_reason, int exit_status)
{
	ft_putstr_err("bash: ");
	ft_putstr_err(error_factor);
	ft_putstr_err(": ");
	ft_putendl_err(error_reason);
	exit(exit_status);
}
