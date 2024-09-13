/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:49:55 by oussama           #+#    #+#             */
/*   Updated: 2024/09/13 18:50:32 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_to_egal(char *first)
{
	int	i;

	i = 0;
	if (first[0] != '_' && (ft_isalpha(first[0]) == 0))
	{
		write(2, "export: ", 8);
		write(2, first, ft_strlen(first));
		write(2, ": not a valid identifier\n", 26);
		return (NULL);
	}
	else if (check_plus(first))
	{
		while (first[i] && first[i] != '+')
		{
			if (!ft_isalnum(first[i]) && first[i] != '_')
				return (NULL);
			i++;
		}
	}
	else
	{
		i = 1;
		while (first[i] && first[i] != '=')
		{
			if (!ft_isalnum(first[i]) && first[i] != '_')
				return (NULL);
			i++;
		}
	}
	return (first);
}
char	*delet_plus(char *str)
{
	int		i;
	char	*s;
	char	*d;

	i = 0;
	while (str[i] != '+' && str[i])
		i++;
	if (str[i + 1] != '=')
		return (NULL);
	s = ft_substr(str, 0, i);
	free(str);
	if (!s)
		return (NULL);
	d = ft_strjoin(s, "=");
	free(s);
	if (!d)
		return (NULL);
	return (d);
}

int	check_exist_node_with_ncmp(char *str, t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_cmp(tmp->key, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
int	check_exist_node_with_cmp(char *str, t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	join_node(char *str, char *data_fin, t_envp **env)
{
	t_envp	*tmp;
	char	*new_data;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			new_data = ft_strjoin(tmp->value, data_fin);
			if (new_data == NULL)
			{
				printf("error ft_strjoin\n");
				return ;
			}
			free(tmp->value);
			tmp->value = new_data;
			return ;
		}
		tmp = tmp->next;
	}
}
