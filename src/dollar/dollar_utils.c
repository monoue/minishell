/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:58:09 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/14 21:52:41 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        *go_parse_dq(char *argv, t_list *envp)
{
     char    **tmp;
    char    *str;
    int     i;
    int     j;
    int     tmp_num;
    char    *variable;
    char    *value;
    char    *arg;

    i = 0;
    j = 0;
    flag_single_in_dq = 0;
    tmp_num = count_command_line_words(argv);
	tmp = malloc(sizeof(*tmp) * (tmp_num + 1000));
    variable = NULL;
    if (!(str = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (!(value = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    arg = ft_strdup(argv);
    while (arg[i])
    {
        variable = NULL;
        arg = ft_substr(arg, i, ft_strlen(arg) - i);
        i = 0;
        if (arg[i] != '\"')
            variable = do_parse2(arg, &i);
        if (variable)
        {
            tmp[j] = ft_strdup(variable);
            j++;
        }
        else
            i++;
        free(variable);
    }
    j = 0;
    while (tmp[j])
    {
        if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
			str = replace_dollar_value(tmp[j], envp, 1);
        else
            str = ft_strdup(tmp[j]);
        value = ft_strnjoin_free(value, str, ft_strlen(str));
        free (str);
        j++;
    }
    ft_free_split(tmp);
    return (value);
}

int     is_char_or_not(char *str, char c)
{
    int     i;

    i = 0;
    while(str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char    *replace_word(const char *head, char *cut_word,
        const char *word)
{
    char    *ret;
    int     length;
    int     i;
    int     j;
    int     f;
    int     count;
    int     cut_count;

    count = ft_strlen(word);
    cut_count = ft_strlen(cut_word);
    length = ft_strlen(head) + count - cut_count;
    if (!(ret = malloc(length + 1)))
        return (NULL);
    i = 0;
    j = 0;
    f = 0;
    while(i < length)
    {
        if (head[i] == '\'')
        {
            ret[i] = head[f];
            i++;
            f++;
            f = f + cut_count;
            while (j < count)
            {
                ret[i] = word[j];
                i++;
                j++;
            }
            ret[i] = head[f];
            i++;
            f++;
        }
        ret[i] = head[f];
        i++;
        f++;
    }
    ret[i] = '\0';
    return (ret);
}

char    *put_single_quotes(char *str)
{
    int     i;
    int     j;
    char    *tmp;

    if (!(tmp = malloc(ft_strlen(str) + 2)))
        exit_err_msg(MALLOC_ERR);
    i = 0;
    j = 0;
    tmp[j] = '\'';
    j++;
    while (str[i])
    {
        tmp[j] = str[i];
        i++;
        j++;
    }
    tmp[j] = '\'';
    j++;
    return (tmp);
}

bool	ft_isascii1(int n)
{
	return (n != '\'' && n != '\"' && n != '$' && n != '/' && n != '\\');
}