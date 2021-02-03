# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2021/02/03 10:48:06 by monoue           ###   ########.fr        #
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

OBJ_DIR			= objs

LIBFT =				$(LIBFT_PATH)libft.a


SRCS  = main.c \
		op_list.c \
		$(COMMAND_PATH)cd_command.c \
		$(COMMAND_PATH)echo_command.c \
		$(PARSER_PATH)count_cmd_line_words.c \
		$(PARSER_PATH)exec_command_chunk.c \
		$(PARSER_PATH)get_redirection_type.c \
		$(PARSER_PATH)is_quote.c \
		$(PARSER_PATH)is_quoted_wrongly.c \
		$(PARSER_PATH)is_redirection.c \
		$(PARSER_PATH)is_reproduction.c \
		$(PARSER_PATH)set_redirections_if.c \
		$(PARSER_PATH)process_command_line.c \
		$(PARSER_PATH)process_one_command.c \
		$(PARSER_PATH)set_fds.c \
		$(PARSER_PATH)space_n_tab_split.c \
		$(PARSER_PATH)split_command_line.c \
		$(EXIT_PATH)exit.c

# SRCS  = main.c \
# 		op_list.c \
# 		$(COMMAND_PATH)cd_command.c \
# 		$(COMMAND_PATH)echo_command.c \
# 		$(COMMAND_PATH)env_command.c \
# 		$(COMMAND_PATH)exit_command.c \
# 		$(COMMAND_PATH)export_command.c \
# 		$(COMMAND_PATH)help_command.c \
# 		$(COMMAND_PATH)no_pipe_command.c \
# 		$(COMMAND_PATH)pwd_command.c \
# 		$(COMMAND_PATH)unset_command.c \
# 		$(COMMAND_PATH)utils_command.c \
# 		$(COMMAND_PATH)utils_command2.c \
# 		$(PARSER_PATH)count_cmd_line_words.c \
# 		$(PARSER_PATH)get_redirection_type.c \
# 		$(PARSER_PATH)is_quote.c \
# 		$(PARSER_PATH)is_quoted_wrongly.c \
# 		$(PARSER_PATH)is_redirection.c \
# 		$(PARSER_PATH)is_reproduction.c \
# 		$(PARSER_PATH)set_fds.c \
# 		$(PARSER_PATH)space_n_tab_split.c \
# 		$(PARSER_PATH)split_command_line.c \
# 		$(EXIT_PATH)exit.c

OBJS = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $(CFLAGS) $^ -L$(LIBFT_PATH) -lft -o $@

all: $(NAME)

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
