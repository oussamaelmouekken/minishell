/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:52:03 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/16 18:57:56 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_lexer(t_lexer **lexer)
{
	while ((*lexer)->next)
	{
		if ((*lexer)->type != WORD && (*lexer)->type != REDIRECT_INPUT
			&& (*lexer)->type != REDIRECT_APPEND)
		{
			if (ft_strlen((*lexer)->value) > 1)
				return (1);
		}
		(*lexer) = (*lexer)->next;
		if ((*lexer)->type == PIPE && ((*lexer)->prev == NULL
				|| (*lexer)->prev->type != WORD))
			return (1);
		if ((*lexer)->type != WORD && (*lexer)->prev->type != WORD
			&& (*lexer)->prev->type != PIPE)
			return (1);
	}
	return (0);
}

int	final_checks(t_lexer **lexer)
{
	if ((*lexer)->type != WORD && ft_strlen((*lexer)->value) >= 2)
		return (1);
	else if ((*lexer)->type == PIPE)
		return (1);
	else if ((*lexer)->type != WORD)
		return (1);
	return (0);
}

int	check_syntax_error(t_lexer **lexer)
{
	if (is_lexer_null(lexer))
		return (0);
	if (is_initial_pipe(lexer))
		return (1);
	if (process_lexer(lexer))
		return (1);
	return (final_checks(lexer));
}

int	syntax_error(t_lexer *lexer)
{
	int		n;
	t_lexer	*new;

	new = lexer;
	n = check_syntax_error(&new);
	if (n != 0)
	{
		if (n == 1)
			print_error(&lexer, "minshell :syntax error near unexpected token",
				new->value);
		return (1);
	}
	return (0);
}
