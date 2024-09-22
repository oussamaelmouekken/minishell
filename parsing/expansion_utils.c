/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:42:01 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 00:59:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value_by_key(char *key)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(g_var_globale.g_exit_status);
	else if (ft_isdigit(key[0]))
		value = key + 1;
	else if (key[0] == '\'' || key[0] == '"')
		value = key;
	else
	{
		value = ft_getenv(key);
		if (value == NULL)
			value = ft_strdup("");
	}
	return (value);
}

char	*handle_digit(char *str, int *i, char *final_str)
{
	char	*key;

	key = NULL;
	(*i)++;
	key = append_alnum(key, str, i);
	final_str = ft_strjoin(final_str, get_value_by_key(key));
	return (final_str);
}

char	*handle_alnum(char *str, int *i, char *final_str)
{
	char	*key;

	key = NULL;
	(*i)++;
	key = append_alnum(key, str, i);
	final_str = ft_strjoin(final_str, get_value_by_key(key));
	return (final_str);
}

char	*handle_special_char(int *i, char *final_str, char special_char)
{
	char	*key;

	key = NULL;
	(*i) += 2;
	key = append_char_to_string(key, special_char);
	final_str = ft_strjoin(final_str, get_value_by_key(key));
	return (final_str);
}

char	*handle_quote(char *str, int *i, char *final_str)
{
	char	*key;

	key = NULL;
	(*i)++;
	key = get_from_quotes(key, str, i);
	final_str = ft_strjoin(final_str, get_value_by_key(key));
	return (final_str);
}
