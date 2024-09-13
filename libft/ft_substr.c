/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:06:24 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/03 19:15:10 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char  *s, int start, int len)
{
	int	i;
	char	*p;
	char	*ss;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	p = malloc((len + 1)); // i9dr iw93 double free  fsplit ila khdmt bmalloc dyali
	ss = (char *)s;
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = ss[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
