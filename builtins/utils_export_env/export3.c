/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:05:31 by oussama           #+#    #+#             */
/*   Updated: 2024/09/18 12:13:16 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_data(char *str, char *fin, t_envp **env)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			gc_remove_ptr(tmp->value);
			tmp->value = fin;
			return ;
		}
		tmp = tmp->next;
	}
}

void	check_egal_and_addegal(char *str, t_envp **env)
{
	t_envp	*tmp;
	char	*new_name;

	tmp = *env;
	while (tmp)
	{
		if (ft_cmp(tmp->key, str) == 0 && tmp->key[ft_strlen(tmp->key)
				- 1] != '=')
		{
			new_name = ft_strjoin(tmp->key, "=");
			if (new_name == NULL)
			{
				printf("error ft_strjoin\n");
				return ;
			}
			gc_remove_ptr(tmp->key);
			tmp->key = new_name;
			tmp->egal_exist = false;
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

int	if_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	free_2(char *first, char *fin)
{
	gc_remove_ptr(first);
	gc_remove_ptr(fin);
}

int	ft_strlen_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
