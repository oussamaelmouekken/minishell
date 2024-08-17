/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:17:41 by oussama           #+#    #+#             */
/*   Updated: 2024/08/17 21:19:36 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(t_command *cmd, t_envp **env)
{
	int i = 1;
	while (cmd->command_chain[i])
	{
		char *target = ft_strjoin(cmd->command_chain[i], "=");
		if (!target)
		{
			printf("error\n");
			exit(0);
		}
		t_envp *tmp = *env;
		t_envp *prev = NULL;
		while (tmp != NULL)
		{
			if (ft_cmp(target, tmp->key) == 0)
			{
				if (prev == NULL)
					*env = tmp->next;
				else
					prev->next = tmp->next;

				free(tmp->value);
				free(tmp->key);
				free(tmp);
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		free(target);
		i++;
	}
}