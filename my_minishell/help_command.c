#include "minishell.h"

char	*builtin_str1[] = {
	"cd",
	"help",
	"exit",
};

int	num_builtins1()
{
	return (sizeof(builtin_str1) / sizeof(char *));
}

int	help()
{
	
	int	i;

	// printf("Type program names and arguments, and hit enter.\n");
	// printf("The following are built in: \n");
	ft_putstr("Type program names and arguments, and hit enter.\n");
	ft_putstr("The following are built in: \n");
	i = 0;	
	while (i < num_builtins1())
	{
		ft_putstr(builtin_str1[i]);
		ft_putstr("\n");
		i++;
	}
	return (1);
}
