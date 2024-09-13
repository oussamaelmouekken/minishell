/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:48:54 by oussama           #+#    #+#             */
/*   Updated: 2024/09/13 18:49:29 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_list(t_envp **env)
{
	t_envp	*tmp;
	int		is_swaped;
	char	*new_data;
	char	*new_name;

	if (*env == NULL)
		return ;
	new_data = NULL;
	new_name = NULL;
	do
	{
		is_swaped = 0;
		tmp = *env;
		while (tmp->next != NULL)
		{
			if (ft_cmp(tmp->key, tmp->next->key) > 0)
			{
				new_name = tmp->next->key;
				tmp->next->key = tmp->key;
				tmp->key = new_name;
				new_data = tmp->next->value;
				tmp->next->value = tmp->value;
				tmp->value = new_data;
				is_swaped = 1;
			}
			tmp = tmp->next;
		}
	} while (is_swaped); // while true
}
int	check_if_egal_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
void	check_egal(t_envp **env)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (check_if_egal_exit(tmp->key) == 1)
		{
			tmp->egal_exist = false;
		}
		else
		{
			tmp->egal_exist = true;
		}
		tmp = tmp->next;
	}
}
int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '=' || s2[i] == '=')
		return (0);
	return (s1[i] - s2[i]);
}

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+' && str[i] == '=')
		return (1);
	else
		return (0);
}
