/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:48:54 by oussama           #+#    #+#             */
/*   Updated: 2024/09/18 12:12:06 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_node(t_envp *node1, t_envp *node2)
{
	char	*new_data;
	char	*new_name;

	new_name = node2->key;
	node2->key = node1->key;
	node1->key = new_name;
	new_data = node2->value;
	node2->value = node1->value;
	node1->value = new_data;
}

void	sort_list(t_envp **env)
{
	t_envp	*tmp;
	int		is_swapped;

	if (*env == NULL)
		return ;
	is_swapped = 1;
	while (is_swapped)
	{
		is_swapped = 0;
		tmp = *env;
		while (tmp->next != NULL)
		{
			if (ft_cmp(tmp->key, tmp->next->key) > 0)
			{
				swap_node(tmp, tmp->next);
				is_swapped = 1;
			}
			tmp = tmp->next;
		}
	}
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
