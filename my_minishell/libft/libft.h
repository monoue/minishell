/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:56:31 by monoue            #+#    #+#             */
/*   Updated: 2021/01/21 16:04:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# include "get_next_line.h"
# include "./ft_printf/ft_printf.h"

# define INT_MIN_STR "-2147483648"
# define MIN(x, y)		((x) <= (y) ? (x) : (y))
# define MAX(x, y)		((x) >= (y) ? (x) : (y))
# define CTOI(c)		c - '0'
# define ITOC(c)		c + '0'
# define ERROR			-1
# define NOT_SET		-1
# define SAFE_FREE(ptr)	{free(ptr);ptr = NULL;}

# define ESC		"\033"
# define RED_S		ESC"[31:1m"
# define GREEN_S	ESC"[32:1m"
# define YELLOW_S	ESC"[33:1m"
# define BLUE_S		ESC"[34:1m"
# define PURPLE_S	ESC"[35:1m"
# define CYAN_S		ESC"[36:1m"
# define RESET		ESC"[m"

typedef enum	e_colors{
	RED_N,
	GREEN_N,
	YELLOW_N,
	BLUE_N,
	PURPLE_N,
	CYAN_N,

	COLORS_NUM
}				t_colors;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

bool				ft_isalnum(int c);
bool				ft_isalpha(int c);
bool				ft_isascii(int n);
bool				ft_isdigit(int c);
bool				ft_isprint(int c);
bool				ft_isspace(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *original_s);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
																size_t len);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strnlen(const char *s, size_t maxlen);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *str, char sep_c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
														void (*del)(void *));
size_t				ft_count_strs(const char **strs);
size_t				ft_intlen(int n);
void				ft_putchar(char c);
void				ft_putstr(char *s);
void				ft_putnbr(int n);
bool				ft_str_is_numeric(const char *str);
char				*ft_strjoin_free_both(char *s1, char *s2);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup_free(char *original_s);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_ctoa(char c);
char				*ft_utoa(unsigned int num);
char				*ft_xtoa(unsigned num);
void				ft_putendl(char *s);
char				ft_itoc(int n);
bool				ft_strequal(const char *s1, const char *s);
void				ft_free_split(char **strs);
void				ft_putstr_err(char *s);
void				put_color_fd(const char *str, t_colors color, int fd);

#endif
