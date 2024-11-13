/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:17:41 by oussama           #+#    #+#             */
/*   Updated: 2024/09/22 13:40:47 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_and_free(char *input)
{
	write(2, "exit\n", 5);
	free(input);
}

void	remove_var(t_envp **envp, char *var_name)
{
	t_envp	*new;
	t_envp	*tmp;

	new = *envp;
	tmp = NULL;
	while (new)
	{
		if (!ft_strcmp(var_name, new->key))
		{
			if (tmp)
				tmp->next = new->next;
			gc_remove_ptr(new->key);
			if (new->value)
				gc_remove_ptr(new->value);
			if (!tmp)
				*envp = (*envp)->next;
			gc_remove_ptr(new);
			return ;
		}
		tmp = new;
		new = new->next;
	}
}

void	unset(t_command *cmd, t_envp **env)
{
	int	i;

	i = 1;
	while (cmd->command_chain[i])
	{
		remove_var(env, cmd->command_chain[i]);
		i++;
	}
}
