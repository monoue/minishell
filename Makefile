# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2021/02/17 16:03:48 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
AR = ar
ARFLAGS = rcs
CC = gcc
CFLAGS = -g

# PATH
SRCS_PATH		= src/
MAIN_UTILS_PATH	= main_utils/
SORT_FILES_PATH	= sort_files/
PARSER_PATH		= parser/
COMMAND_PATH	= command/
DOLLAR_PATH		= dollar/
EXIT_PATH		= exit/
SYNTAX_ERROR_CHECK_PATH	= syntax_error_check/
LIBFT_PATH		= libft/

INCLUDE	= -I./libft -I./src/includes

BASE	  = $(MAIN_UTILS_PATH)put_greeting.c \
			$(MAIN_UTILS_PATH)get_env_list.c \
			$(MAIN_UTILS_PATH)set_signal_handlers.c \
			op_list.c \
			test_functions.c \
			$(DOLLAR_PATH)dollar.c \
			$(DOLLAR_PATH)dollar_utils.c \
			$(DOLLAR_PATH)dollar_utils2.c \
			$(DOLLAR_PATH)dollar_utils3.c \
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
			$(PARSER_PATH)count_command_line_words.c \
			$(PARSER_PATH)exec_command_chunk.c \
			$(PARSER_PATH)exec_reproduction.c \
			$(PARSER_PATH)exec_path_command.c \
			$(PARSER_PATH)ft_split_skipping_quotes.c \
			$(PARSER_PATH)get_continuous_quotes_trimmed_strs.c \
			$(PARSER_PATH)get_redirection_type.c \
			$(PARSER_PATH)has_pipe.c \
			$(PARSER_PATH)is_escaped.c \
			$(PARSER_PATH)is_reproduction.c \
			$(PARSER_PATH)is_specific_char_not_escaped.c \
			$(PARSER_PATH)is_symbol_char.c \
			$(PARSER_PATH)is_symbol_str.c \
			$(PARSER_PATH)process_redirections.c \
			$(PARSER_PATH)split_command_line.c \
			$(PARSER_PATH)str_is_quoted.c \
			$(PARSER_PATH)process_command_line.c \
			$(PARSER_PATH)process_one_command.c \
			$(PARSER_PATH)process_pipes.c \
			$(PARSER_PATH)remove_quotes.c \
			$(PARSER_PATH)set_fds.c \
			$(PARSER_PATH)set_words.c \
			$(PARSER_PATH)set_redirection.c \
			$(PARSER_PATH)skip_chunk.c \
			$(PARSER_PATH)skip_quotes.c \
			$(PARSER_PATH)skip_word.c \
			$(PARSER_PATH)turn_dollar_question_into_value.c \
			$(PARSER_PATH)count_command_line_words.c \
			$(SYNTAX_ERROR_CHECK_PATH)is_str_empty.c \
			$(SYNTAX_ERROR_CHECK_PATH)is_quoted_wrongly.c \
			$(SYNTAX_ERROR_CHECK_PATH)check_syntax.c \
			$(SYNTAX_ERROR_CHECK_PATH)put_message_if_syntax_error.c \
			$(EXIT_PATH)exit.c

SRCS_NAME = $(BASE) main.c
TEST_NAME = $(BASE) test.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
TEST = $(addprefix $(SRCS_PATH), $(TEST_NAME))
OBJS = $(SRCS:%.c=%.o)
DEPS	= $(SRCS:.c=.d)
TOBJS = $(TEST:%.c=%.o)
LIBFT	= libft/libft.a

.c.o:
		$(CC) $(CFLAGS) $(INCLUDE) -c -MMD -MP -MF $(<:.c=.d) $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $@ $^

-include $(DEPS)

$(LIBFT):
	make -C libft

all: $(NAME)

test: $(TOBJS) $(LIBFT)
	@$(CC) -o $@ $^

bonus: $(BOBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $^ -L$(LIBFT_PATH) -lft -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME) test

re: fclean all

.PHONY: all clean fclean re run
