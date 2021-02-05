/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:41:34 by sperrin           #+#    #+#             */
/*   Updated: 2021/02/05 15:30:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char **argv, t_list *envp)
{
	int		arg_i;
	int		env_i;
	int		target_prev_i;
	char	*key;
	t_list	*target;


	//やってることはリスト構造体の中に、例えば１０、２０、３０、４０、５０が入ってる
	//３０を消したい場合は、
	//２０までポインタを進んで、それまで30のデータが指していたデータ40を20が指すようにして、リストから30を外します。
	//あとは、temp に取り置いていた３０をfreeします。
	arg_i = 1;
	env_i = 0;
	while (argv[arg_i])
	{
		key = get_key(argv[arg_i]);//”KEY=”までを取る
		if (same_key(key, envp) == 1)
		{
			target_prev_i = get_target_prev_i(key, envp);//どこで消したい環境変数があるを探してる
			while (env_i < target_prev_i)//２０までポインタを進んでる　
			{
				envp = envp->next;
				env_i++;
			}
			target = envp->next;//tmpリスト構造体に３０を入れて
    		envp->next = target->next;//20の次を40とする
			free(target);//３０をFREEする
		}
		free(key);
		arg_i++;
	}
}
