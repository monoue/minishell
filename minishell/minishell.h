/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/02/05 17:36:50 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../debug.h"

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

# define ERR_MSG		"error: "
# define FATAL_ERR_MSG	ERR_MSG"fatal\n"
# define MALLOC_ERR		"memory allocation error\n"
# define PROMPT			"\033[31m$❯\033[0m "
# define OUTPUT			">"
# define APPEND			">>"
# define INPUT			"<"
# define OPEN_MODE		0666
# define EXIT_INVALID	128
# define LLONG_MAX_DIGITS	19

#define SYNTAX_VALID			-10
#define SYNTAX_QUOTED_WRONGLY	-20

pid_t	pid;
int		flag;

typedef enum	e_element_type {
	START,
	PIPE_OR_BREAK,
	REDIRECTION,
	NEWLINE,
	WORD,

	ELEMENT_TYPES_NUM
}				t_element_type;

typedef enum	e_type
{
	TYPE_INPUT,
	TYPE_OUTPUT,
	TYPE_APPEND,

	TYPES_NUM
}				t_type;

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
** put_welcome_picture
*/
void	put_welcome_picture(void);
void	put_farewell_picture(void);

/*
** commands
*/
void			pwd(char **argv);
int				help();
int				exit_minishell(char **argv);
void    		cd(char **argv, t_list *envp);
void			echo(char **argv);
void		    env(t_list *envp);
void			export(char **argv, t_list *envp);
void			unset(char **argv, t_list *envp);
char     		*dollar(char *argv, t_list *envp);

/*
**  syntax_error_check
*/
bool			str_is_of_spaces(char *str);
bool			put_message_if_syntax_error(char *command_line);

/*
** parser
*/
int				check_syntax(char *command_line, char **command_line_words);
size_t			count_command_line_words(char const *str);
char			**ft_split_skipping_quotes(char const *str, char sep_c);
int				get_redirection_type(char *element);
bool			is_reproduction(char *word);
bool			is_redirection_char(char c);
bool			is_redirection_str(char *str);
int				is_quote(char c);
bool			is_space_or_tab(char c);
bool			is_pipe_or_break_char(char c);
bool			is_pipe_or_break_str(char *str);
bool			is_metachar(char c);
bool			is_metachar_str(char *str);
void			process_command_line(char *line, t_list *envp);
void			process_one_command(char *command, t_list *envp);
void			set_fds(t_fd *fds);
size_t			process_redirections(char **chunk_words, t_fd *fds);
void			skip_quotes(char const *str, size_t *index);
// char			**space_and_tab_split(char const *str);
// int				process_pipes(char **piped_chunks, size_t i, size_t chunks_num);
void			exec_command_chunk(char *command_chunk, t_list *envp);
bool			is_quoted_wrongly(char *str);
// char			**split_cmd_line(char const *str);
// bool			is_redirection(char c);
char			**split_command_line(char const *str);

/*
** utils command
*/
bool			is_command(char *argv);
// bool			pipe_or_not_pipe(t_chunk *chunk);
void			ascii_sort(char **args);
bool			check_valid_arg(char *argv);
// bool			is_valid_arg(char *argv);

/*
** utils command 2
*/
char    *get_key(char *argv);
void	*delete_variable(void *ptr);
bool	same_key(char *key, t_list *envp);
int		get_target_prev_i(char *key, t_list *envp);
char    **turn_envp_into_strs(t_list *envp);

/*
** utils command 3
*/
char    *ft_strcat(char *dest, char *src);
int		ft_strrchr_int(const char *s, int c);
void	add_variable(char *argv, t_list *envp);
int     dollar_or_not(char *argv, int c);

/*
** exit
*/
void	exit_fatal(void);
void	exit_err_msg(char *err_msg);
#endif