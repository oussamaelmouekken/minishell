/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:50:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 01:07:14 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*gc_malloc(size_t size)
{
	void		*ptr;
	t_gc_node	*new_node;

	ptr = malloc(size);
	if (ptr)
	{
		new_node = malloc(sizeof(t_gc_node));
		if (!new_node)
		{
			free(ptr);
			return (NULL);
		}
		new_node->ptr = ptr;
		new_node->is_freed = 0;
		new_node->next = g_var_globale.gc;
		g_var_globale.gc = new_node;
	}
	return (ptr);
}

void	gc_free_all(void)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = g_var_globale.gc;
	while (current)
	{
		next = current->next;
		if (current->is_freed == 0)
		{
			free(current->ptr);
		}
		free(current);
		current = next;
	}
	g_var_globale.gc = NULL;
}

void	gc_remove_ptr(void *ptr)
{
	t_gc_node	*current;

	current = g_var_globale.gc;
	while (current)
	{
		if (current->ptr == ptr && current->is_freed == 0)
		{
			current->is_freed = 1;
			free(current->ptr);
			return ;
		}
		current = current->next;
	}
}
