/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:13:53 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 01:00:24 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(char *key)
{
	t_envp	*current;
	char	*current_key_without_equal;

	current = g_var_globale.envp;
	while (current != NULL)
	{
		current_key_without_equal = ft_remove_equal(current->key);
		if (is_equal(current_key_without_equal, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*to_fin(char *str)
{
	int		i;
	int		j;
	char	*s;
	int		c;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	c = ft_strlen(str) - i;
	s = gc_malloc(sizeof(char) * (c + 1));
	if (!s)
	{
		printf("error gc_malloc\n");
		return (NULL);
	}
	j = 0;
	while (i < ft_strlen(str))
	{
		s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}

char	*to_egal(char *str)
{
	int		i;
	int		j;
	char	*s;

	s = NULL;
	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	s = gc_malloc(sizeof(char) * (i + 1));
	if (!s)
	{
		printf("error gc_malloc\n");
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

int	erro_malloc(t_envp *n)
{
	if (n == NULL)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	return (0);
}

void	init_(t_envp *new_node)
{
	new_node->env_path = false;
	new_node->egal_exist = false;
}
