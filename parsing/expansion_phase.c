/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_phase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:22:22 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:28:52 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_quotes(char *key, char *str, int *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote = str[*i];
		key = append_char_to_string(key, quote);
		(*i)++;
		while (str[*i] && str[*i] != quote)
		{
			key = append_char_to_string(key, str[*i]);
			(*i)++;
		}
		if (str[*i] == quote)
		{
			key = append_char_to_string(key, quote);
			(*i)++;
		}
	}
	return (key);
}

void	process_dollar_sign(char *str, t_expansion_vars *phase)
{
	if (str[phase->i] == '$' && isdigit(str[phase->i + 1])
		&& phase->inside_single_quotes == 1)
		phase->final_str = handle_digit(str, &(phase->i), phase->final_str);
	else if (str[phase->i] == '$' && is_alnum_or_underscore(str[phase->i + 1])
		&& phase->inside_single_quotes == 1)
		phase->final_str = handle_alnum(str, &(phase->i), phase->final_str);
	else if (str[phase->i] == '$' && str[phase->i + 1] == '?'
		&& phase->inside_single_quotes == 1)
		phase->final_str = handle_special_char(&(phase->i), phase->final_str,
				'?');
	else if (str[phase->i] == '$' && str[phase->i + 1] == '$'
		&& phase->inside_single_quotes == 1)
		phase->final_str = handle_special_char(&(phase->i), phase->final_str,
				'$');
	else if (str[phase->i] == '$' && (str[phase->i + 1] == '\'' || str[phase->i
				+ 1] == '"') && phase->inside_single_quotes == 1)
		phase->final_str = handle_quote(str, &(phase->i), phase->final_str);
	else
	{
		phase->final_str = append_char_to_string(phase->final_str,
				str[phase->i]);
		phase->i++;
	}
}

void	process_key(char *str, t_expansion_vars *phase)
{
	while (str[phase->i] != '\0')
	{
		if (str[phase->i] == '\'' && phase->inside_double_quotes == 1)
			phase->inside_single_quotes *= -1;
		else if (str[phase->i] == '"' && phase->inside_single_quotes == 1)
			phase->inside_double_quotes *= -1;
		if (str[phase->i] == '$')
			process_dollar_sign(str, phase);
		else
		{
			phase->final_str = append_char_to_string(phase->final_str,
					str[phase->i]);
			phase->i++;
		}
	}
}

char	*expansion(char *str)
{
	t_expansion_vars	phase;

	phase.i = 0;
	phase.inside_single_quotes = 1;
	phase.inside_double_quotes = 1;
	phase.final_str = ft_strdup("");
	while (str[phase.i])
		process_key(str, &phase);
	return (phase.final_str);
}

void	expansion_phase(t_lexer **lexer)
{
	t_lexer	*current;
	int		skip_expansion;

	skip_expansion = 0;
	g_var_globale.export_encountered = 0;
	current = *lexer;
	while (current != NULL)
	{
		if (current->type == REDIRECT_INPUT || current->type == REDIRECT_OUT
			|| current->type == REDIRECT_APPEND || current->type == REDIRECT_IN)
			skip_expansion = 1;
		else if (current->type == WORD)
		{
			if (!skip_expansion)
				current->value = expansion(current->value);
			if (strcmp(current->value, "export") == 0)
				g_var_globale.export_encountered = 1;
			skip_expansion = 0;
		}
		else
			skip_expansion = 0;
		current = current->next;
	}
}
