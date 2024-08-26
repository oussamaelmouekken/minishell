/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:48:42 by oussama           #+#    #+#             */
/*   Updated: 2024/08/26 17:57:54 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_n(char *flag)
{
	int	i;

	i = 0;
	if (ft_strlen(flag) <= 1)
		return (0);
	if (flag[0] != '-')
		return (0);
	i++;
	while (flag[i])
	{
		if (flag[i] != 'n') // different de n
			return (0);
		i++;
	}
	return (1); // egal == 'n'
}
int	check_befor(char **str, int end)
{
	int	i;
	int	j;

	i = 1;
	while (i < end)
	{
		j = 0;
		if (str[i][j] == '-')
			j++;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
void	echo_n(t_command *cmd)
{
	int	flag;
	int	i;

	if (cmd->command_chain[1] == NULL)
		return ;
	if (cmd->command_chain[1][0] != 'n' || cmd->command_chain[1][0] != '-')
		flag = 0;
	i = 1;
	while (cmd->command_chain[i])
	{
		flag = flag_n(cmd->command_chain[i]);
		if (cmd->command_chain[1][1] != 'n' || (check_befor(cmd->command_chain,
					i) && flag == 1))
			flag = 0;
		if (flag == 0)
		{
			printf("%s", cmd->command_chain[i]);
			if (cmd->command_chain[i + 1])
				printf(" ");
		}
		i++;
	}
	if (check_newline(cmd->command_chain[1]))
		printf("\n");
	return ;
}
