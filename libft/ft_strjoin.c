/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:13:49 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/11 16:09:39 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	k;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2);
	j = ft_strlen(s1);
	p = malloc(k + 1);
	if (!p)
		return (NULL);
	ft_strlcpy( p,s1, j + 1);
	ft_strlcat(p, s2, k + 1);
	return (p);
}
