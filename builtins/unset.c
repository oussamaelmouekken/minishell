/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:17:41 by oussama           #+#    #+#             */
/*   Updated: 2024/09/14 22:43:27 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			free(new->key);
			if (new->value)
				free(new->value);
			if (!tmp)
				*envp = (*envp)->next;
			free(new);
			return ;
		}
		tmp = new;
		new = new->next;
	}
}
void unset(t_command *cmd, t_envp **env)
{
    int i;

    i = 1;
    while (cmd->command_chain[i])
    {
        remove_var(env, cmd->command_chain[i]);
        i++;
    }
}

