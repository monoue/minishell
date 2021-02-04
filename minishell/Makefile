# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2021/02/04 16:13:29 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
AR = ar
ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# PATH
LIBFT_PATH		= ../libft/
SORT_FILES_PATH	= sort_files/
PARSER_PATH		= parser/
COMMAND_PATH	= command/
EXIT_PATH		= exit/
SYNTAX_ERROR_CHECK_PATH	= syntax_error_check/

LIBFT =				$(LIBFT_PATH)libft.a


SRCS  = main.c \
		prompt_cat.c \
		op_list.c \
		$(COMMAND_PATH)cd_command.c \
		$(COMMAND_PATH)pwd_command.c \
 		$(COMMAND_PATH)echo_command.c \
 		$(COMMAND_PATH)env_command.c \
 		$(COMMAND_PATH)exit_command.c \
 		$(COMMAND_PATH)export_command.c \
 		$(COMMAND_PATH)help_command.c \
 		$(COMMAND_PATH)unset_command.c \
		$(COMMAND_PATH)utils_command.c \
		$(COMMAND_PATH)utils_command2.c \
		$(COMMAND_PATH)utils_command3.c \
		$(COMMAND_PATH)dollar.c \
		$(PARSER_PATH)count_command_line_words.c \
		$(PARSER_PATH)exec_command_chunk.c \
		$(PARSER_PATH)ft_split_considering_quotes.c \
		$(PARSER_PATH)get_redirection_type.c \
		$(PARSER_PATH)is_reproduction.c \
		$(PARSER_PATH)is_symbol_char.c \
		$(PARSER_PATH)is_symbol_str.c \
		$(PARSER_PATH)process_redirections.c \
		$(PARSER_PATH)split_command_line.c \
		$(PARSER_PATH)process_command_line.c \
		$(PARSER_PATH)process_one_command.c \
		$(PARSER_PATH)set_fds.c \
		$(PARSER_PATH)skip_quotes.c \
		$(PARSER_PATH)count_command_line_words.c \
		$(SYNTAX_ERROR_CHECK_PATH)is_str_empty.c \
		$(SYNTAX_ERROR_CHECK_PATH)is_quoted_wrongly.c \
		$(SYNTAX_ERROR_CHECK_PATH)check_syntax.c \
		$(EXIT_PATH)exit.c

OBJS = $(SRCS:%.c=%.o)
TOBJS = $(TEST:%.c=%.o)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $(CFLAGS) $^ -L$(LIBFT_PATH) -lft -o $@

all: $(NAME)

test: $(TOBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $(CFLAGS) $^ -L$(LIBFT_PATH) -lft -o test

bonus: $(BOBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $^ -L$(LIBFT_PATH) -lft -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re run
