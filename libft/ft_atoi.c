/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:43 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/15 17:05:02 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void print(char *str)
{
	write(2 ,"exit: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	//printf("%d\n",sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
		{
			print(str);
			return (2);
		}
		nb = nb * 10 + (str[i++] - '0');
	}
	return (sign * nb);
}
