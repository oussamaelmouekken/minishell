/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:08:30 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:16:57 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_for_closed_quotes(char *input)
{
	char	*str;
	char	current_quote;

	str = input;
	current_quote = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			current_quote = *str;
			str++;
			while (*str != '\0' && *str != current_quote)
				str++;
			if (*str == '\0')
				return (0);
		}
		str++;
	}
	return (1);
}

char	*append_alnum(char *key, char *str, int *i)
{
	while (str[*i] && is_alnum_or_underscore(str[*i]))
	{
		key = append_char_to_string(key, str[*i]);
		(*i)++;
	}
	return (key);
}

void	free_lexer_list(t_lexer **lexer)
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
