# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2021/01/27 11:31:11 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

# PATH
LIBFT_PATH =		libft/
SORT_FILES_PATH =	sort_files/
PARSER_PATH =		parser/
COMMAND_PATH =		command/

LIBFT =				$(LIBFT_PATH)libft.a

SRCS_NAME =
# CFLAGS = -Wall -Wextra -Werror

SRCS  = main.c \
		op_list.c \
		$(COMMAND_PATH)cd_command.c \
		$(COMMAND_PATH)echo_command.c \
		$(COMMAND_PATH)env_command.c \
		$(COMMAND_PATH)exit_command.c \
		$(COMMAND_PATH)export_command.c \
		$(COMMAND_PATH)help_command.c \
		$(COMMAND_PATH)no_pipe_command.c \
		$(COMMAND_PATH)pwd_command.c \
		$(COMMAND_PATH)unset_command.c \
		$(COMMAND_PATH)utils_command.c \
		$(COMMAND_PATH)utils_command2.c \
		$(PARSER_PATH)is_quote.c \
		$(PARSER_PATH)is_quoted_wrongly.c \
		$(PARSER_PATH)is_redirection.c \
		$(PARSER_PATH)count_cmd_line_words.c \
		$(PARSER_PATH)split_cmd_line.c

OBJS = $(SRCS:%.c=%.o)


$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH);
	@$(CC) $^ -L$(LIBFT_PATH) -lft -o $@

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
