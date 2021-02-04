/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/04 14:05:29 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **argv, t_list *envp)
{
	int		i;
	int		env;
	int		tmp_env;
	char	*key;
	t_list	*tmp;


	//やってることはリスト構造体の中に、例えば１０、２０、３０、４０、５０が入ってる
	//３０を消したい場合は、
	//２０までポインタを進んで、それまで30のデータが指していたデータ40を20が指すようにして、リストから30を外します。
	//あとは、temp に取り置いていた３０をfreeします。
	i = 1;
	env = 0;
	while (argv[i])
	{
		key = check_key(argv[i]);//”KEY=”までを取る
		if (same_key(key, envp) == 1)
		{
			tmp_env = get_content(key, envp);//どこで消したい環境変数があるを探してる
			while (env < tmp_env)//２０までポインタを進んでる　
			{
				envp = envp->next;
				env++;
			}
			tmp = envp->next;//tmpリスト構造体に３０を入れて
    		envp->next = tmp->next;//20の次を40とする
			free(tmp);//３０をFREEする
		}
		i++;
	}
}
