/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:14 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/15 12:18:42 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     space;

char     *replace_dollar_value(char *argv, t_list *envp, int flag)
{
    int     count;
    char    *variable;
    char    *tmp_var;
    char    *value;
    char    *arg;
    t_list  *tmp_list;
    int     flag_sq;

    
    flag_sq = 0;
    flag_single_in_dq = 0;
    space = 0;
    if (!(variable = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (!(arg = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (!(tmp_var = ft_strdup("")))
        exit_err_msg(MALLOC_ERR);
    if (argv[0] == '\"')
    {
        arg = remove_quotes(argv);
        if (single_quotation_or_not(arg))
        {
            flag_single_in_dq = 1;
            free(arg);
            return(do_single_quotation(argv, envp));
        }
        flag = 1;
    }
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
        value = skip_space_dollar(tmp_var);
        space = 1;
    }
    else
        value = ft_strdup(tmp_var);
    free(tmp_var);
    flag = 0;
    if (ft_strcmp(value, "") == 0)
            return (NULL);
    return (value);
}

char    *do_parse(char *line, int *i)
{
        char    *tmp;
        int     count_dq_extern;
        int     count_dq_intern;

        flag_single_in_dq = 0;
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
                if (line[*i] == '$')
                {
                    tmp = ft_strdup("(process ID)");
                    (*i)++;
                    return (tmp);
                }
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                while (line[*i] != '\'' && line[*i] != '\"' &&
                        line[*i] != '\0' && line[*i] != '$' && line[*i] != '/'
                        && line[*i] != '\\' && line[*i] != '=' && !ft_isdigit(line[*i]))
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
            if (line[*i] == '\"')
            {
                tmp = ft_strnjoin_free(tmp, &line[*i], 1);
                (*i)++;
                while (line[*i] != '\"')
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
                        && line[*i] != '$' && line[*i] != '\0')
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

char    *dollar(char *argv, t_list *envp)
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
    // tmp = (char**)malloc(1000);
    // variable = (char**)malloc(1000);
    // str = ft_strdup("");
    // value = ft_strdup("");
    // arg = ft_strdup(argv);
    tmp_num = count_command_line_words(argv);
	tmp = malloc(sizeof(*tmp) * (tmp_num + 10000));
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
        variable = do_parse(arg, &i);
        if (variable)
            tmp[j] = ft_strdup(variable);
        j++;
        free(variable);
    }
    j = 0;
    while (tmp[j])
    {
        if (dollar_or_not(tmp[j], '$') && tmp[j][0] == '\"')
            str = go_parse_dq(tmp[j], envp);
        else if (dollar_or_not(tmp[j], '$') && tmp[j][0] != '\'')
			str = replace_dollar_value(tmp[j], envp, 0);
        else
            str = remove_quotes(ft_strdup(tmp[j]));
        // value = ft_strjoin(value, str);
        value = ft_strnjoin_free(value, str, ft_strlen(str));
        free(str);
        j++;
    }
    char *final;
    final = remove_escape(value);
    ft_free_split(tmp);
    return(final);
}
//めちゃくちゃ汚いので綺麗にするつもり、でももっとシンプルな書き方を見つければぜひ直して欲しい！