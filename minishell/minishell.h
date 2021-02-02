/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/01/28 06:59:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../debug.h"

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define ERR_MSG		"error: "
# define FATAL_ERR_MSG	ERR_MSG"fatal\n"
# define MALLOC_ERR		"memory allocation error\n"
# define PROMPT			"❯ "
# define OUTPUT			">"
# define APPEND			">>"
# define INPUT			"<"
# define OPEN_MODE		0666
# define EXIT_INVALID	128

__BEGIN_DECLS
extern int * __error(void);
#define errno (*__errosr())
__END_DECLS

// typedef			enum
// {
// 	TYPE_END,
// 	TYPE_PIPE,
// 	TYPE_BREAK,
// 	TYPE_INPUT,
// 	TYPE_OUTPUT,
// 	TYPE_APPEND,

// 	TYPES_NUM
// }				t_type;

typedef			enum
{
	TYPE_INPUT,
	TYPE_OUTPUT,
	TYPE_APPEND,

	TYPES_NUM
}				t_type;
// typedef struct	s_chunk
// {
// 	char			**argv;
// 	size_t			size;
// 	t_type			type;
// 	// int				fds[2];

// 	struct s_chunk	*prev;
// 	struct s_chunk	*next;
// }				t_chunk;

typedef struct	s_redirection_set
{
	t_type			type;
	char			*filename;
	// 下、両方は要らないかも	
	// struct s_chunk	*prev;
	struct s_redirection_set	*next;
}				t_redirection_set;

typedef struct	s_redirection_combination {
	char	*symbol;
	t_type	type;
}				t_redirection_combination;


// typedef struct	s_type_flag {
// 	t_type	type;
// 	int		flags;	
// }				t_type_flag;

typedef enum	e_redirection {
	REDIRECT_INPUT,
	REDIRECT_OVERRIDE,
	REDIRECT_APPEND,
	REDIRECT_NUM,
}				t_redirection;

typedef struct	s_fd {
	int	input;
	int	output;
}				t_fd;
/*
** list operation
*/
t_redirection_set	*lstlast(t_redirection_set *chunk);
void				lstadd_back(t_redirection_set **chunks,
											t_redirection_set *new);




/*
** commands
*/
// void			pwd(t_chunk *chunk);
// int				help();
// int				minishell_exit();
// int				cd(char **args);
// void			echo(t_chunk *chunk);
// void		    env(t_list *envp);
// void			export(t_chunk *chunk, t_list *envp);
// void			unset(t_chunk *chunk, t_list *envp);
// void			no_pipe(t_chunk *chunk, t_list *envp);

/*
** parser
*/
void			process_command_line(void);
char			**space_and_tab_split(char const *str);
int				get_redirection_type(char *element);
bool			is_reproduction(char *word);
void			set_fds(t_fd *fds);
bool			is_redirection_char(char c);
bool			is_redirection_str(char *str);
t_redirection_set	*make_redirection_list(char **elements);

// bool			is_syntax_wrong(char *str);
// char			**split_cmd_line(char const *str);
bool			is_quote(char c);
// bool			is_redirection(char c);
size_t			count_cmd_line_words(char const *str);
char			**split_command_line(char const *str);

/*
** utils command
*/
bool			is_command(char *argv);
// bool			pipe_or_not_pipe(t_chunk *chunk);
void			ascii_sort(char **args);
bool			check_valid_arg(char *argv);
bool			arg_is_str(char *argv);

/*
** utils command 2
*/
char			*check_key(char **argv);
void			*delete_variable(void *ptr);
bool			is_key_duplicated(char *key, t_list *envp);
#endif

/*
** exit
*/
void	exit_fatal(void);
void	exit_err_msg(char *err_msg);