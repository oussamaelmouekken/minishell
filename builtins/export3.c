/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:05:31 by oussama           #+#    #+#             */
/*   Updated: 2024/09/13 19:37:23 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_data(char *str, char *fin, t_envp **env)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			free(tmp->value);
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
			free(tmp->key);
			tmp->key = new_name;
			tmp->egal_exist = false;
			return;
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
	free(first);
	free(fin);
}

int	ft_strlen_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}