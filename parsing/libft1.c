/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:27:45 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:13:35 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	gc_remove_ptr_lexer_list(t_lexer **lexer)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lexer;
	while (current != NULL)
	{
		next = current->next;
		gc_remove_ptr(current->value);
		gc_remove_ptr(current);
		current = next;
	}
	*lexer = NULL;
}

int	is_alnum_or_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_lexer	*create_lexer_node(char *value, enum e_token_type type)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)gc_malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->value = ft_strdup(value);
	new_node->type = type;
	new_node->next = NULL;
	gc_remove_ptr(value);
	return (new_node);
}

t_lexer	*get_last_node(t_lexer *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	append_lexer_node(t_lexer **lexer, t_lexer *new_node)
{
	t_lexer	*last;

	if (*lexer == NULL)
	{
		*lexer = new_node;
	}
	else
	{
		last = get_last_node(*lexer);
		last->next = new_node;
		new_node->prev = last;
	}
}
