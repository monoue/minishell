#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define HAS_NO_CHILD 0
# define ERROR		-1
# define TYPE_END	3
# define TYPE_PIPE	4
# define TYPE_BREAK	5

# define READ_END	0
# define WRITE_END	1

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
	int				pipefds[2];
	struct s_base	*previous;
	struct s_base	*next;
}				t_chunk;

int		ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(char const *str);

#endif