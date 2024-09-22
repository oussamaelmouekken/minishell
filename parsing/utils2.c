/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:16:33 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:06:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_char_to_string(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str == NULL)
	{
		new_str = (char *)gc_malloc(2);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	else
	{
		new_str = (char *)gc_malloc(ft_strlen(str) + 2);
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = c;
		new_str[i + 1] = '\0';
	}
	return (new_str);
}

size_t	strlen_to_char(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

char	*ft_remove_equal(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = ft_strlen_to_char(str, '=');
	result = gc_malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

int	is_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (1);
}
