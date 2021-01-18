#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>

# define TYPE_END	3
# define TYPE_PIPE	4
# define TYPE_BREAK	5

// typedef struct	s_list
// {
// 	char			**args;
// 	int				length;
// 	int				type;
// 	int				pipes[2];
// 	struct s_list	*previous;
// 	struct s_list	*next;
// }				t_list;

typedef struct	s_base
{
	char			**argv;
	int				size;
	int				type;
	int				fds[2];
	struct s_base	*previous;
	struct s_base	*next;
}				t_base;

int		ft_strlen(char *str);
char	ft_strcpy(char *dst, char *src);
char	ft_strdup(char const *str);

#endif