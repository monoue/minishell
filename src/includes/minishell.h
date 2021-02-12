/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/02/12 11:35:25 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "debug.h"

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
# define SYNTAX_ERROR	258
# define LLONG_MAX_DIGITS	19
# define AMBIGUOUS_ERR	"ambiguous redirect"
# define NO_COMMANDS_ERR	"command not found"
# define QUIT_MSG	"Quit: 3"
# define TRASH_REMOVER	"\b \b\b  \b\b"
# define DOLLAR_Q		"$?"
# define COMMAND_NOT_FOUND	127

#define SYNTAX_VALID			-10
#define SYNTAX_QUOTED_WRONGLY	-20

pid_t	g_pid;
int		flag;
extern int		g_last_exit_status;

typedef enum	e_element_type {
	START,
	PIPE_OR_BREAK,
	REDIRECTION,
	NEWLINE,
	WORD,

	ELEMENT_TYPES_NUM
}				t_element_type;

typedef enum	e_quote
{
	NOT_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}				t_quote;

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
** main
*/
t_list	*get_env_list(void);
void		set_signal_handlers(void);
/*
** put_welcome_greeting
*/
void	put_welcome_greeting(void);
void	put_farewell_greeting(void);

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
char			*replace_dollar_value(char *argv, t_list *envp);

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
bool			is_escaped(const char *str, size_t index);
bool			is_reproduction(char *word);
bool			is_redirection_char(char c);
bool			is_redirection_str(char *str);
t_quote			get_quote_type(char c);
bool			is_space_or_tab(char c);
bool			is_specific_char_not_escaped(const char *str, size_t index, bool(*func)(char));
bool			is_pipe_or_break_char(char c);
bool			is_pipe_or_break_str(char *str);
bool			is_metachar(char c);
bool			is_metachar_str(char *str);
void			process_command_line(char *line, t_list *envp);
void			process_one_command(char *command, t_list *envp);
char			*remove_quotes(const char *str);
void			set_fds(t_fd *fds);
void			skip_chunk(char const *str, size_t *index);
void			skip_word(const char *str, size_t *index);
bool			str_is_quoted(const char *str);
size_t			process_redirections(char **chunk_words, t_fd *fds, t_list *envp);
void			skip_quotes(char const *str, size_t *index);
// char			**space_and_tab_split(char const *str);
// int				process_pipes(char **piped_chunks, size_t i, size_t chunks_num);
void			exec_command_chunk(char *command_chunk, t_list *envp);
bool			is_quoted_wrongly(char *str);
// bool			is_redirection(char c);
char			**split_command_line(char const *str);
void			set_words(const char *str, char **words, size_t words_num);
bool			is_quote_char(char c);

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
char    **turn_envp_into_strs(t_list *envp);

/*
** utils command 3
*/
char    *ft_strcat(char *dest, char *src);
int		ft_strrchr_int(const char *s, int c);
void	add_variable(char *argv, t_list *envp);
int		dollar_or_not(char *argv, int c);
// bool	is_env(char *arg);

/*
** exit
*/
void	exit_fatal(void);
void	exit_err_msg(char *err_msg);
void	exit_bash_err_msg(const char *error_factor, const char *error_reason, int exit_status);

// debug
void	print_strs(char **strs);
#endif