# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: monoue <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 15:33:41 by monoue            #+#    #+#              #
#    Updated: 2021/01/26 07:33:14 by monoue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g

# PATH
LIBFT_PATH =		libft/
SORT_FILES_PATH =	sort_files/
PRINTER_PATH =		printer/

LIBFT =				$(LIBFT_PATH)libft.a

SRCS_NAME =
# CFLAGS = -Wall -Wextra -Werror

SRCS  = cd_command.c \
		echo_command.c \
		env_command.c \
		exit_command.c \
		export_command.c \
		help_command.c \
		is_quoted_wrongly \
		main.c \
		op_list.c \
		pwd_command.c \
		split_cmd_line.c \
		wc_command.c

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
