/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:10:53 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/18 12:11:23 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fct1(char *first, char *str, char *fin)
{
	free_2(first, fin);
	write(2, "export: ", 8);
	write(2, str, ft_strlen(str));
	write(2, "not a valid identifier\n", 24);
	g_var_globale.g_exit_status = 1;
	return ;
}

int	fct2(char *str, t_envp *env, char *fin)
{
	char	*first;
	char	*new_first;
	char	*n;

	first = to_egal(str);
	new_first = check_to_egal(first);
	n = delet_plus(new_first);
	if (n == NULL)
	{
		fct1(first, str, fin);
		return (0);
	}
	if (check_exist_node_with_ncmp(n, env))
	{
		join(n, env, fin);
		return (0);
	}
	else
	{
		add_v(n, fin, env);
		return (0);
	}
	return (1);
}

int	fct3(char *first, char *fin, char *new_first, t_envp *env)
{
	check_egal_and_addegal(new_first, &env);
	change_data(new_first, fin, &env);
	gc_remove_ptr(first);
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
		if (handle_check_plus(str, env, first, fin))
			return ;
	}
	else if (check_exist_node_with_ncmp(new_first, env))
	{
		if (check_exist_node(new_first, env, first, fin))
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
