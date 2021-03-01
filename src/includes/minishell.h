/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 07:40:11 by monoue            #+#    #+#             */
/*   Updated: 2021/03/02 08:08:41 by monoue           ###   ########.fr       */
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
# define AMBIGUOUS_ERR		"ambiguous redirect"
# define NO_COMMANDS_ERR	"command not found"
# define QUIT_MSG			"Quit: 3"
# define TRASH_REMOVER		"\b \b\b  \b\b"
# define DOLLAR_Q			"$?"
# define COMMAND_NOT_FOUND	127
# define SYMBOL_CHARS		"\\\'~*()/|<>[]{};?!"
# define SYNTAX_VALID			-10
# define SYNTAX_QUOTED_WRONGLY	-20
# define OVER_UCHAR_MAX			-1
# define OVER_INT_MAX			-2
# define SUCCESS				0

pid_t	g_pid;
int		g_last_exit_status;

bool	g_space;
bool	g_flag;
bool	g_flag_escape_db;
bool	g_flag_dont;
bool	g_global;
bool	g_into_dollar;

typedef enum		e_element_type {
	START,
	PIPE_OR_BREAK,
	REDIRECTION,
	NEWLINE,
	WORD,

	ELEMENT_TYPES_NUM
}					t_element_type;

typedef enum		e_type
{
	TYPE_INPUT,
	TYPE_OUTPUT,
	TYPE_APPEND,

	TYPES_NUM
}					t_type;

typedef struct		s_redirection_set
{
	t_type						type;
	int							designated_fd;
	char						*filename;
	struct s_redirection_set	*next;
}					t_redirection_set;

typedef struct		s_redirection_combination {
	char	*symbol;
	t_type	type;
}					t_redirection_combination;

typedef enum		e_redirection {
	REDIRECT_INPUT,
	REDIRECT_OVERRIDE,
	REDIRECT_APPEND,
	REDIRECT_NUM,
}					t_redirection;

typedef struct		s_fd {
	int	input;
	int	output;
}					t_fd;

/*
** list operation
*/
t_redirection_set	*lstlast(t_redirection_set *chunk);
void				lstadd_back(t_redirection_set **chunks,
											t_redirection_set *new);

/*
** main
*/
t_list				*get_env_list(void);
void				set_signal_handlers(void);
/*
** put_welcome_greeting
*/
void				put_welcome_greeting(void);
void				put_farewell_greeting(void);

/*
** commands
*/
void				pwd(char **argv);
int					help();
void				exit_minishell(char **argv);
void				cd(char **argv, t_list *envp);
void				echo(char **argv);
void				env(t_list *envp);
void				export(char **argv, t_list *envp);
void				unset(char **argv, t_list *envp);
void				put_error_invalid_identifier(const char *command,
															const char *arg);

bool				digits_num_is_over_llong_max(const char *str);

/*
** dollar
*/
char				*dollar(char *argv, t_list *envp);
char				*replace_dollar_value(char *argv, t_list *envp);

/*
** dollar_utils
*/
char				*go_parse_dq(char *argv, t_list *envp, int j);
char				*find_key_1(char *argv, t_list *envp);
char				*replace_word(const char *head, char *cut_word,
													const char *word, int i);
char				*put_single_quotes(char *str);
bool				ft_isascii1(int n);

/*
** dollar_utils2
*/
char				*skip_space_dollar(char *value);
char				*do_single_quotation(char *argv, t_list *envp, int j);
int					single_quotation_or_not(char *argv);
char				*take_dollar_dq(char *line, int *i);
char				**do_parse2(char *line);

/*
** dollar_utils3
*/
char				*find_key(char *arg, t_list *envp);
char				*take_dollar(char *line, int *i);
char				*take_single_quote(char *line, int *i);
char				*take_ascii(char *line, int *i);
char				*take_double_quote(char *line, int *i);

/*
** dollar_utils4
*/
char				*take_escape(char *line, int *i);
char				*into_single_quotes(char *argv, int *i);
int					count_variable(char *variable);
// char				*return_final(char *str, char **tmp, int j);
char				*return_final(char *str, bool head_is_single_quote);
char				**do_parse3(char *line);
// char				*remove_final(char *str, char **tmp, int j);
char				*remove_final(char *str, bool head_is_single_quote);

/*
** dollar_utils5
*/
char				*take_dollar_bis(char *line, int *i, char *tmp);

/*
**  syntax_error_check
*/
bool				str_is_of_tabs_or_spaces(char *str);
bool				put_message_if_syntax_error(char *command_line);
int					check_syntax(char *command_line, char **command_line_words);

/*
** parser
*/
int					check_syntax(char *command_line, char **command_line_words);
size_t				count_command_line_words(char const *str);
char				*cut_out_meta_char(const char *str, size_t *index);
void				exec_path_command(char **argv, t_list *envp);
void				exec_reproduction(char **argv, t_list *envp);
char				**extract_argv(char **chunk_words);
char				**ft_split_skipping_quotes(char const *str, char sep_c);
char				*get_continuous_quotes_trimmed_str(char *str);
char				**get_continuous_quotes_trimmed_strs(char **src_strs);
int					get_redirection_type(const char *element);
void				handle_exec_error(const char *command);
void				has_pipe(char **piped_chunks, t_list *envp,
															size_t chunks_num);
bool				is_escaped(const char *str, size_t index);
bool				is_reproduction(char *word);
bool				is_redirection_char(char c);
bool				is_redirection_str(const char *str);
bool				is_redirection_str_partial(const char *str);
bool				is_space_or_tab(char c);
bool				is_specific_char_not_escaped(const char *str, size_t index,
															bool(*func)(char));
bool				is_pipe_or_break_char(char c);
bool				is_pipe_or_break_str(char *str);
bool				is_metachar(char c);
bool				is_metachar_str(char *str);
t_redirection_set	*make_redirection_set(char **elements);
void				process_command_line(char *line, t_list *envp);
void				process_one_command(char *command, t_list *envp);
char				*remove_quotes(const char *str);
void				reset_redirection_fds(t_fd *fds);
void				set_fds(t_fd *fds);
int					set_redirection(t_redirection_set *set, t_fd *fds);
void				skip_chunk(char const *str, size_t *index);
void				skip_redirection(const char *str, size_t *index);
void				skip_word(const char *str, size_t *index);
bool				str_is_quoted(const char *str);
char				*turn_dollar_question_into_value(const char *str);
int					process_redirections(char **chunk_words, t_fd *fds,
																t_list *envp);
void				skip_quotes(char const *str, size_t *index);
void				skip_spaces(const char *str, size_t *index);
void				exec_command_chunk(char *command_chunk, t_list *envp,
															bool pipe_child);
bool				is_quoted_wrongly(char *str);
char				**split_command_line(char const *str);
void				set_words(const char *str, char **words, size_t words_num);
bool				str_is_quoted_by_double(const char *str);
bool				is_quote_char(char c);
char				*remove_escape(const char *str);
char				*remove_escape_dq(const char *str);

/*
** utils command
*/
bool				is_command(char *argv);
void				ascii_sort(char **args);
bool				check_valid_arg(char *argv);

/*
** utils command 2
*/
char				*get_key(char *argv);
void				*delete_variable(void *ptr);
bool				same_key(char *key, t_list *envp);
char				**turn_envp_into_strs(t_list *envp);

/*
** utils command 3
*/
char				*ft_strcat(char *dest, char *src);
int					ft_strrchr_int(const char *s, int c);
void				add_variable(char *argv, t_list *envp);
int					dollar_or_not(char *argv, int c);
// bool				dollar_or_not(char *argv, int c);
long long			ft_atoll(const char *str);
unsigned long long	ft_atoull(const char *str);
void				put_error_numeric(char *argv);

/*
** exit
*/
void				exit_fatal(void);
void				exit_err_msg(char *err_msg);
void				exit_bash_err_msg(const char *error_factor,
								const char *error_reason, int exit_status);
void				put_bash_err_msg(const char *error_factor,
													const char *error_reason);

#endif
