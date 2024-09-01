/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:42:24 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/31 14:26:57 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int size_of_list(t_envp *env)
{
	int i = 0;
	while(env)
	{
		i++;
		env = env->next;
	}
	return i;
}
char **add_env_arr(t_envp *env)
{
	t_envp *tmp = env;
	int i = 0;
	char **str = malloc(sizeof(char *) * (size_of_list(env) + 1));
    if (!str)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
	while(tmp)
	{
		str[i] = ft_strjoin(tmp->key,tmp->value);
		if(str[i] == NULL)
		{
			printf("error copy env\n");
		 	return NULL;
		}
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return str;
}
