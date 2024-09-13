/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_phase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:34:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/04 12:05:27 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *append_char_to_string(char *str, char c)
{
	char *new_str;
	int i;

	i = 0;
	if (str == NULL)
	{
		new_str = (char *)malloc(2);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	else
	{
		new_str = (char *)malloc(ft_strlen(str) + 2);
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

char *append_alnum(char *key, char *str, int *i)
{
	while (str[*i] && is_alnum_or_underscore(str[*i]))
	{
		key = append_char_to_string(key, str[*i]);
		(*i)++;
	}
	return (key);
}

char *expansion(char *str, t_envp *list_envp)
{
	int i;
	int inside_single_quotes;
	int inside_double_quotes;
	char *key;
	char *final_str;

	i = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	key = NULL;
	final_str = str;
	while (str[i])
	{
		if (str[i] == '"' && inside_double_quotes == 0)
			inside_double_quotes = 1;
		else if (str[i] == '"' && inside_double_quotes == 1)
			inside_double_quotes = 0;
		else if (str[i] == '\'' && !inside_double_quotes && inside_single_quotes == 0)
		{
			inside_single_quotes = 1;
			break;
		}
		if (!inside_single_quotes && str[i] == '$' && ft_isdigit(str[i + 1]))
		{
			i += 1;
			key = append_alnum(key, str, &i);
			final_str = replace_env_keys_with_values(final_str, key, list_envp);
			key = NULL;
		}
		else if (!inside_single_quotes && str[i] == '$' && is_alnum_or_underscore(str[i + 1]))
		{
			i += 1;
			key = append_alnum(key, str, &i);
			final_str = replace_env_keys_with_values(final_str, key, list_envp);
			free(key);
			key = NULL;
		}
		else if (!inside_single_quotes && str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			key = append_char_to_string(key, '?');
			final_str = replace_env_keys_with_values(final_str, key, list_envp);
			free(key);
			key = NULL;
		}
		else if (!inside_single_quotes && str[i] == '$' && str[i + 1] == '$')
		{
			i += 2;
			key = append_char_to_string(key, '$');
			final_str = replace_env_keys_with_values(final_str, key, list_envp);
			free(key);
			key = NULL;
		}
		else
			i++;
	}
	return (final_str);
}

void expansion_phase(t_lexer **lexer, t_envp *list_envp)
{
	t_lexer *current;
	char *str;

	current = *lexer;
	while (current != NULL)
	{
		if (current->type == WORD)
		{
			if (current->prev == NULL || current->prev->type != REDIRECT_INPUT)
			{
				str = expansion(current->value, list_envp);
				current->value = str;
			}
		}
		current = current->next;
	}
}
