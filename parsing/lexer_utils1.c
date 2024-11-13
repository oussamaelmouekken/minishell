/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 00:41:42 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:33:48 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_lexer_phase(t_lexer_state *phase)
{
	phase->inside_quotes = 0;
	phase->current_word_len = 0;
	phase->start = 0;
	phase->i = 0;
}

void	process_current_word(t_lexer_state *state, char *input, void *lexer)
{
	if (state->current_word_len > 0)
	{
		state->current_word = ft_substr(input, state->start,
				state->current_word_len);
		append_lexer_node(lexer, create_lexer_node(state->current_word, WORD));
		state->current_word_len = 0;
	}
	state->start = state->i + 1;
}

void	process_redirect(t_lexer_state *state, char *input)
{
	if (input[state->i] == '>')
		state->type = REDIRECT_APPEND;
	else
		state->type = REDIRECT_INPUT;
	state->current_word = ft_substr(input + state->i, 0, 2);
	state->i++;
}

void	process_redirect1(t_lexer_state *state, char *input)
{
	if (input[state->i] == '>')
		state->type = REDIRECT_OUT;
	else
		state->type = REDIRECT_IN;
	state->current_word = ft_substr(input + state->i, 0, 1);
}

void	process_pipe(t_lexer_state *state, char *input)
{
	state->type = PIPE;
	state->current_word = ft_substr(input + state->i, 0, 1);
}
