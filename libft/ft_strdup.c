/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:42:37 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/18 11:47:38 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*d;
	int		j;

	j = ft_strlen(src);
	i = 0;
	d = gc_malloc(sizeof(char) * (j + 1));
	if (!d)
		return (0);
	while (src[i])
	{
		d[i] = src[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
