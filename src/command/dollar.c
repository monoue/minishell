/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/10 14:27:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char     *skip_space_for_the_fucking_no_dblquo_dollar(char *value)
{
    int     i;
    int     j;
    char    *tmp;

    i = 0;
    j = 0;
    tmp = malloc(1000);
    while (value[i])
    {
        if ((!is_space_or_tab(value[i])) || (is_space_or_tab(value[j + i - 1]) && !is_space_or_tab(value[j + i])))
        {
            tmp[j] = value[i];
            j++;
        }
        i++;
    }
    return (tmp);
}

char    *remove_quotes_by_me(char *argv)
{
    char    *tmp;
    int     i;

    i = 0;
    tmp = ft_strdup("");
    while (argv[i])
    {
        if (argv[i] == '\"')
        {
            while (argv[i] != '\"')
            {
                tmp[i] = argv[i];
                i++;
            }
            return (tmp);
        }
        i++; 
    }
    return (NULL);
}

char     *replace_dollar_value(char *argv, t_list *envp)
{
    int     count;
    char    *variable;
    char    *tmp_var;
    char    *value;
    char    *arg;
    t_list  *tmp_list;
    int     flag;

    flag = 0;
    variable = NULL;
    if (argv[0] == '\"')
    {
        argv = remove_quotes_by_me(argv);
        if (argv[0] == '\'')
            return(argv);
        flag = 1;
    }
    tmp_var = ft_strdup("");
    arg = ft_strjoin(&argv[1], "=");
    tmp_list = envp;
    while (tmp_list && tmp_list->next)
    {
        if (ft_strncmp((char*)tmp_list->content, arg, ft_strlen(arg)) == 0)
            variable = ft_strdup((char*)tmp_list->content);
        tmp_list = tmp_list->next;
    }
    free(arg);
    if (variable)
    {
        count = ft_strrchr_int(variable, '=');
        tmp_var = ft_substr(variable, count + 1, ft_strlen(variable) - count);
        free(variable);
    }
    if (flag == 0)
    {
        value = ft_strdup(skip_space_for_the_fucking_no_dblquo_dollar(tmp_var));
    }
    else
    {
        value = ft_strdup(tmp_var);
    }
    free(tmp_var);
    return (value);
}


bool    ft_isascii1(int n)
{
    return (n != '\'' && n != '\"' && n != '$');
}

char    *do_parse(char *line, int *i)
{
        char    *tmp;
        int     count_dq_extern;
        int     count_dq_intern;

        tmp = malloc(10000);
        count_dq_extern = 0;
        count_dq_intern = 0;
        while(line[*i])
        {
            if (line[*i] == '$')
            {
                tmp[*i] = line[*i];
                    (*i)++;
                while (line[*i] != '\'' && line[*i] != '\"' &&
                        line[*i] != '\0' && line[*i] != '$')
                {
                    tmp[*i] = line[*i];
                    (*i)++;
                }
                return (tmp);
            }
            if (line[*i] == '\'')
            {
                tmp[*i] = line[*i];
                (*i)++;
                while (line[*i] != '\'')
                {
                    tmp[*i] = line[*i];
                    (*i)++;
                }
                tmp[*i] = line[*i];
                (*i)++;
                return (tmp);
            }
            if (line[*i] == '\"')
            {
                tmp[*i] = line[*i];
                (*i)++;
                while (line[*i] != '\"')
                {
                    tmp[*i] = line[*i];
                    (*i)++;
                }
                tmp[*i] = line[*i];
                (*i)++;
                return (tmp);
            }
            if (ft_isascii1(line[*i]))
            {
                while (line[*i] != '\"' && line[*i] != '\'' 
                        && line[*i] != '$' && line[*i] != '\0')
                {
                    tmp[*i] = line[*i];
                    (*i)++;
                }
                return (tmp);
            }
        }
        return (NULL);
}

char    *dollar(char *argv, t_list *envp)
{
    char    **tmp;
    char    *str;
    int     i;
    int     j;
    char    **variable;
    char    *value;
    char    *arg;

    i = 0;
    j = 0;
    tmp = (char**)malloc(1000);
    variable = (char**)malloc(1000);
    str = ft_strdup("");
    value = ft_strdup("");
    arg = ft_strdup(argv);
    while (arg[i])
    {
        int a = 0;
        arg = ft_substr(arg, i, ft_strlen(arg) - i);
        i = 0;
        variable[a] = do_parse(arg, &i);
        if (variable[a])
            tmp[j] = ft_strdup(variable[a]);
        j++;
        free(arg);
        // free(variable);
        a++;
    }
    j = 0;
    while (tmp[j])
    {
        if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
            str = replace_dollar_value(tmp[j], envp);
        else
            str = tmp[j];
        value = ft_strjoin(value, str);
        free(str);
        j++;
    }
    char *final;
    final = remove_quotes(value);
    return (final);
}
