/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:39 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/16 10:27:05 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void remove_quotes(char **str)
{
    int i = 0;
    int j = 0;
    char current_quote;
    char *new_str = (char *)malloc(strlen(*str) + 1);
    if (new_str == NULL)
    {
        free(new_str);
        return;
    }

    while ((*str)[i])
    {
        if ((*str)[i] == '\'' || (*str)[i] == '"')
        {
            current_quote = (*str)[i];
            i++;
            while ((*str)[i] && (*str)[i] != current_quote)
                new_str[j++] = (*str)[i++];
            if ((*str)[i] == current_quote)
                i++;
        }
        else
            new_str[j++] = (*str)[i++];
    }
    new_str[j] = '\0';
    free(*str);
    *str = new_str;
}