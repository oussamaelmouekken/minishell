/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_phase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:21:56 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:35:07 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_current_word1(t_lexer_state *s, char *input, t_lexer **lexer)
{
	if (s->current_word_len > 0)
	{
		s->current_word = ft_substr(input, s->start,
				s->current_word_len);
		append_lexer_node(lexer, create_lexer_node(s->current_word, WORD));
	}
}

void	process_input_character(t_lexer_state *state, char *input, void *lexer)
{
	if (input[state->i] == ' ' || input[state->i] == '\t')
		process_current_word(state, input, lexer);
	else if (input[state->i] == '<' || input[state->i] == '|'
		|| input[state->i] == '>')
	{
		if ((input[state->i] == '>' && input[state->i + 1] == '>')
			|| (input[state->i] == '<' && input[state->i + 1] == '<'))
			process_redirect(state, input);
		else if (input[state->i] == '<' || input[state->i] == '>')
			process_redirect1(state, input);
		else if (input[state->i] == '|')
			process_pipe(state, input);
		append_lexer_node(lexer, create_lexer_node(state->current_word,
				state->type));
	}
	else
		state->current_word_len++;
}

void	reset_quotes_and_increment_word_len(t_lexer_state *state, int var)
{
	state->inside_quotes = var;
	state->current_word_len++;
}

void	lexer_phase(t_lexer **lexer, char *input)
{
	t_lexer_state	state;

	init_lexer_phase(&state);
	while (input[state.i] != '\0')
	{
		if (input[state.i] == '"' && state.inside_quotes == 0)
			reset_quotes_and_increment_word_len(&state, 1);
		else if (input[state.i] == '"' && state.inside_quotes == 1)
			reset_quotes_and_increment_word_len(&state, 0);
		else if (input[state.i] == '\'' && state.inside_quotes == 0)
			reset_quotes_and_increment_word_len(&state, 2);
		else if (input[state.i] == '\'' && state.inside_quotes == 2)
			reset_quotes_and_increment_word_len(&state, 0);
		else if (state.inside_quotes)
			state.current_word_len++;
		else
			process_input_character(&state, input, lexer);
		state.i++;
	}
	process_current_word1(&state, input, lexer);
}
