#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

typedef struct	s_minishell
{
	char	*name;
	char	*current_dir;
}				t_minishell;

typedef struct	s_env
{
	char	*key;
	char	*value;
	
}				t_env;

extern char	**environ;

#endif
