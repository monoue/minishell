/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:59:42 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/15 12:26:00 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char     *skip_space_dollar(char *value)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    j = 0;
    if (!(tmp = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    while (value[i])
    {
        if ((!is_space_or_tab(value[i])) || (is_space_or_tab(value[j + i - 1]) 
                && !is_space_or_tab(value[j + i])))
        {
            if (is_space_or_tab(value[j + i - 1]))
                tmp = ft_strnjoin_free(tmp, " ", 1);
            else
            tmp = ft_strnjoin_free(tmp, &value[i], 1); 
            j++;
        }
        i++;
    }
    return (tmp);
}

char    *do_single_quotation(char *argv, t_list *envp)
{
    char    *buf;
    int     i;
    char    *str;
    char    *value;

    i = 0;
    if (!(str = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (!(value = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (!(buf = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    while (argv[i])
    {
        if (argv[i] == '\'')
        {
            i++;
            while (argv[i] != '\'')
            {
                buf = ft_strnjoin_free(buf, &argv[i], 1);
                i++;
            }
        }
        i++;
    }
    str = replace_dollar_value(buf, envp, 1);
    value = replace_word(argv, buf, str);
    free(str);
    free(buf);
    return (value);
}

int     single_quotation_or_not(char *argv)
{
    int     i;

    i = 0;
    while (argv[i])
    {
        if (argv[i] == '\'')
            return (1);
        i++;
    }
    return (0);
}

char    *do_parse2(char *line, int *i)
{
        char    *tmp;
        int     count_dq_extern;
        int     count_dq_intern;

        if (!(tmp = ft_strdup("")))
            exit_err_msg(MALLOC_ERR);
        count_dq_extern = 0;
        count_dq_intern = 0;
        while(line[*i])
        {
            if (line[*i] == '$')
            {
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                while (line[*i] != '\'' && line[*i] != '\"' &&
                        line[*i] != '\0' && line[*i] != '$' && line[*i] != '/'
                        && line[*i] != '=' && !ft_isdigit(line[*i]))
                {
                    tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                    (*i)++;
                }
                return (tmp);
            }
            if (line[*i] == '\'')
            {
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                while (line[*i] != '\'')
                {
                    tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                    (*i)++;
                }
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                return (tmp);
            }
            if (ft_isascii1(line[*i]))
            {
                while (line[*i] != '\"' && line[*i] != '\'' 
                        && line[*i] != '$' && line[*i] != '\0'
                        && line[*i] != '/')
                {
                    tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                    (*i)++;
                }
                return (tmp);
            }
            if (line[*i] == '/')
            {
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                return(tmp);
            }
            if (line[*i] == '\\')
            {
                while (line[*i] != '$' && line[*i] != '\0' && !ft_isascii1(line[*i]))
                {
                    tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                    (*i)++;
                }
                return(tmp);
            }
        }
        return (NULL);
}