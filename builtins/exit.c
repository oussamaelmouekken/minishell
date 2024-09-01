/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:44:45 by oussama           #+#    #+#             */
/*   Updated: 2024/08/29 17:18:23 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	util(t_command *cmd)
{
	int	new_exit;

	new_exit = 0;
	printf("exit\n");
	new_exit = ft_atoi(cmd->command_chain[1]);
	return (new_exit);
}

int	utils_exit(int is_numeric, t_command *cmd)
{
	if (is_numeric)
	{
		if (cmd->command_chain[2] != NULL)
		{
			printf("exit\nminishell : exit: to many argument\n");
			g_exit_status = 1;
			return (1);
		}
		else
			g_exit_status = util(cmd);
	}
	else
	{
		printf("exit\nexit: %s: numeric argument required\n",
			cmd->command_chain[1]);
		g_exit_status = 2;
		exit(g_exit_status);
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
			if (!ft_isdigit(cmd->command_chain[1][i]))
			{
				is_numeric = 0;
				break ;
			}
			i++;
		}
		if (utils_exit(is_numeric, cmd) == 1)
			return ;
	}
	exit(g_exit_status);
}
