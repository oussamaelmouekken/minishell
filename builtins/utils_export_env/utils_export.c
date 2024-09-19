/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:10:28 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/18 12:13:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	check_exist_node(char *new_first, t_envp *env, char *first, char *fin)
{
	if (if_egal(new_first))
	{
		free_2(first, fin);
		return (1);
	}
	else
	{
		if (fct3(first, fin, new_first, env) == 0)
			return (1);
	}
	return (0);
}

int	handle_check_plus(char *str, t_envp *env, char *first, char *fin)
{
	if (fct2(str, env, fin) == 0)
	{
		gc_remove_ptr(first);
		return (1);
	}
	return (0);
}

void	join(char *n, t_envp *env, char *fin)
{
	check_egal_and_addegal(n, &env);
	join_node(n, fin, &env);
	gc_remove_ptr(n);
}

void	add_v(char *n, char *fin, t_envp *env)
{
	char	*n_and_d;

	n_and_d = ft_strjoin(n, fin);
	ft_add_value_env(n_and_d, &env);
	gc_remove_ptr(n);
	gc_remove_ptr(n_and_d);
	gc_remove_ptr(fin);
}
