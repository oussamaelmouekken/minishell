/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:44:45 by oussama           #+#    #+#             */
/*   Updated: 2024/09/18 12:10:31 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	util(t_command *cmd)
{
	int	new_exit;

	new_exit = 0;
	if (g_var_globale.var->nb_cmd == 1)
		write(2, "exit\n", 5);
	new_exit = ft_atoi(cmd->command_chain[1]);
	return (new_exit);
}

int	utils_exit(int is_numeric, t_command *cmd)
{
	if (is_numeric)
	{
		if (cmd->command_chain[2] != NULL)
		{
			if (g_var_globale.var->nb_cmd == 1)
				write(2, "exit\nexit: to many argument\n", 29);
			g_var_globale.g_exit_status = 1;
			return (1);
		}
		else
			g_var_globale.g_exit_status = util(cmd);
	}
	else
	{
		if (g_var_globale.var->nb_cmd == 1)
			write(2, "exit\nexit: numeric argument required\n", 37);
		g_var_globale.g_exit_status = 2;
		gc_free_all();
		exit(g_var_globale.g_exit_status);
	}
	return (0);
}

void	my_exit(t_command *cmd)
{
	int	is_numeric;
	int	i;

	is_numeric = 0;
	if (cmd->command_chain[1] != NULL)
	{
		is_numeric = 1;
		i = 0;
		while (cmd->command_chain[1][i] != '\0')
		{
			if (!ft_isdigit(cmd->command_chain[1][1])
				&& cmd->command_chain[1][0] != '-')
			{
				is_numeric = 0;
				break ;
			}
			i++;
		}
		if (utils_exit(is_numeric, cmd) == 1)
			return ;
	}
	if (cmd->command_chain[1] == NULL && g_var_globale.var->nb_cmd == 1)
		write(2, "exit\n", 5);
	gc_free_all();
	exit(g_var_globale.g_exit_status);
}
