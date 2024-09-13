/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:10:53 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/13 19:56:03 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fct1(char *first, char *str, char *fin)
{
	free_2(first, fin);
	write(2, "export: ", 8);
	write(2, str, ft_strlen(str));
	write(2, "not a valid identifier\n", 24);
	var_globale.g_exit_status = 1;
	return ;
}
int	fct2(char *str, t_envp *env, char *fin)
{
	char	*first;
	char	*new_first;
	char	*n;
	char	*n_and_d;

	first = to_egal(str);
	new_first = check_to_egal(first);
	n = delet_plus(new_first);
	if (n == NULL)
	{
		fct1(first, str, fin);
		return (0);
	}
	if (check_exist_node_with_ncmp(n, env)) // node exit
	{
		check_egal_and_addegal(n, &env);
		join_node(n, fin, &env);
		free(n);
		return (0);
	}
	else // node not exist
	{
		n_and_d = ft_strjoin(n, fin);
		ft_add_value_env(n_and_d, &env);
		free(n);
		free(n_and_d);
		free(fin);
		return (0);
	}
	return (1);
}

int	fct3(char *first, char *fin, char *new_first, t_envp *env)
{
	check_egal_and_addegal(new_first, &env);
	change_data(new_first, fin, &env);
	 free_2(first, fin);
	return (0);
}

void	check_cmd(char *str, t_envp *env)
{
	char	*new_first;
	char	*first;
	char	*fin;

	first = to_egal(str);
	new_first = check_to_egal(first);
	fin = to_fin(str);
	if (new_first == NULL)
	{
		fct1(first, str, fin);
		return ;
	}
	else if (check_plus(new_first))
	{
		if (fct2(str, env, fin) == 0)
			return ;
	}
	else if (check_exist_node_with_ncmp(new_first, env) && if_egal(new_first))
	{
		free_2(first, fin);
		return ;
	}
	else if (check_exist_node_with_ncmp(new_first, env))
	{
		if (fct3(first, fin, new_first, env) == 0)
			return ;
	}
	ft_add_value_env(str, &env);
	 free_2(first, fin);
}

void	export(t_command *cmd, t_envp **env)
{
	int	i;

	i = 1;
	while (cmd->command_chain[i])
	{
		check_cmd(cmd->command_chain[i], *env);
		i++;
	}
}
