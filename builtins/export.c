/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:10:53 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/29 22:45:34 by oel-moue         ###   ########.fr       */
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
void check_egal(t_envp **env)
{
	t_envp *tmp = *env;
	while(tmp)
	{
		if(check_if_egal_exit(tmp->key) == 1)
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

char	*check_to_egal(char *first)
{
	int	i;

	i = 0;
	if (first[0] != '_' && (ft_isalpha(first[0]) == 0))
	{
		printf("export: %s: not a valid identifier\n", first);
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
	if (!s)
		return (NULL);
	d = ft_strjoin(s, "=");
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
int	check_egal_and_addegal(char *str, t_envp **env)
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
				return (0);
			}
			free(tmp->key);
			tmp->key = new_name;
			tmp->egal_exist = false;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
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

void	check_cmd(char *str, t_envp*env)
{
	char	*new_first;
	char	*first;
	char	*fin;
	char	*n;
	char	*n_and_d;

	first = to_egal(str);
	new_first = check_to_egal(first);
	fin = to_fin(str);
	if (new_first == NULL)
	{
		printf("error\n");
		return ;
	}
	else if (check_plus(new_first))
	{
		n = delet_plus(new_first);
		if (n == NULL)
		{
			printf("error +\n");
			return ;
		}
		if (check_exist_node_with_ncmp(n, env)) // node exit
		{
			if (check_egal_and_addegal(n, &env))
			{
				join_node(n, fin, &env);
				return ;
			}
			join_node(n, fin, &env);
			return ;
		}
		else // node not exist
		{
			n_and_d = ft_strjoin(n, fin);
			if (!n_and_d)
			{
				printf("error strjoin \n");
				return ;
			}
			ft_add_value_env(n_and_d, &env);
			return ;
		}
	}
	else if (check_exist_node_with_ncmp(new_first, env) && if_egal(new_first))
	{
		return ;
	}
	else if (check_exist_node_with_ncmp(new_first, env))
	{
		if (check_egal_and_addegal(new_first, &env))// check if data exist egal(=)
		{
			change_data(new_first, fin, &env);
			return ;
		}
		change_data(new_first, fin, &env);
		return ;
	}
	ft_add_value_env(str, &env);
}

void	export(t_command*cmd, t_envp **env)
{
	if (cmd == NULL || *env == NULL)
	{
		printf("empty env\n");
		return ;
	}
	int i = 1;
	while (cmd->command_chain[i])
	{
		check_cmd(cmd->command_chain[i], *env);
		i++;
	}
}
