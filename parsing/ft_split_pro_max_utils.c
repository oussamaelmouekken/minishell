/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pro_max_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:25:39 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/18 22:26:23 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	toggle_quotes(char c, bool *in_quotes, char *quote_char)
{
	if (c == '"' || c == '\'')
	{
		if (!*in_quotes)
		{
			*in_quotes = true;
			*quote_char = c;
		}
		else if (c == *quote_char)
		{
			*in_quotes = false;
			*quote_char = '\0';
		}
	}
}

int	count_words(char *s)
{
	int		count;
	int		i;
	bool	in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = false;
	quote_char = '\0';
	while (s && s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && !in_quotes)
			i++;
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] != '\0' && (in_quotes || (s[i] != ' ' && s[i] != '\t')))
		{
			toggle_quotes(s[i], &in_quotes, &quote_char);
			i++;
		}
	}
	return (count);
}
