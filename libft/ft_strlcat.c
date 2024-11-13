/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 23:02:11 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/18 11:47:57 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, char *src, int dstsize)
{
	int	i;
	int	j;
	int	k;
	int	c;

	if (dest && src && dstsize == 0)
		return (0);
	c = ft_strlen(src);
	k = ft_strlen(dest);
	if (dstsize == 0 || dstsize < k || !dest)
		return (c + dstsize);
	i = k;
	j = 0;
	while (src[j] && i < (dstsize - 1))
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (k + c);
}
