/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:48:42 by oussama           #+#    #+#             */
/*   Updated: 2024/08/10 18:24:34 by oel-moue         ###   ########.fr       */
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

void	echo_n(char **cmd)
{
	int		flag;
	int		i;

	if(cmd[1] == NULL)
	 return;
	if(cmd[1][0] != 'n' || cmd[1][0] != '-')
			flag = 0;
	// if(cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] != 'n')
	//   d = 1;
	i = 1;
	while (cmd[i])
	{
		flag = flag_n(cmd[i]);
		if(cmd[1][1] != 'n' || (cmd[i - 1][1] != 'n' && i != 1))
		{
		 	flag = 0;
		}
		if (flag == 0)
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
		}
		i++;
	}
	if (cmd[1][1] != 'n') // firts agr # -n.....
		printf("\n");
	return ;
}
