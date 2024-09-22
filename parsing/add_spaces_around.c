/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces_around.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:19:07 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:29:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_modified_input(const char *input)
{
	char	*modified_input;

	modified_input = gc_malloc(strlen(input) * 4 + 1);
	if (modified_input == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	return (modified_input);
}

void	initialize_t_parser_state(t_parser_state *state, const char *input)
{
	state->i = 0;
	state->j = 0;
	state->inside_double_quotes = 0;
	state->inside_single_quotes = 0;
	state->modified_input = allocate_modified_input(input);
}

void	process_input(t_parser_state *state, const char *input)
{
	if ((input[state->i] == '|' && input[state->i + 1] == '|'))
		return ;
	state->modified_input[state->j++] = ' ';
	state->modified_input[state->j++] = input[state->i];
	if ((input[state->i] == '>' && input[state->i + 1] == '>')
		|| (input[state->i] == '<' && input[state->i + 1] == '<'))
		state->modified_input[state->j++] = input[++state->i];
	state->modified_input[state->j++] = ' ';
}

char	*add_spaces_around_special_chars(const char *input)
{
	t_parser_state	state;

	initialize_t_parser_state(&state, input);
	while (input[state.i] != '\0')
	{
		if (input[state.i] == '"')
		{
			state.inside_double_quotes = !state.inside_double_quotes;
			state.modified_input[state.j++] = input[state.i];
		}
		else if (input[state.i] == '\'')
		{
			state.inside_single_quotes = !state.inside_single_quotes;
			state.modified_input[state.j++] = input[state.i];
		}
		else if (!state.inside_double_quotes && !state.inside_single_quotes
			&& (input[state.i] == '<' || input[state.i] == '|'
				|| input[state.i] == '>'))
			process_input(&state, input);
		else
			state.modified_input[state.j++] = input[state.i];
		state.i++;
	}
	state.modified_input[state.j] = '\0';
	return (state.modified_input);
}
