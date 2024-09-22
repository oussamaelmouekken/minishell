/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:54:53 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/16 18:57:42 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(t_lexer **lexer, char *str, char *str1)
{
	if (str1 && ft_strlen(str1) > 1)
		printf("%s`%c%c'\n", str, str1[0], str1[1]);
	else if (str1)
		printf("%s`%c'\n", str, str1[0]);
	else
		printf("%s\n", str);
	*lexer = NULL;
	return (0);
}

int	is_lexer_null(t_lexer **lexer)
{
	return (!(*lexer));
}

int	is_initial_pipe(t_lexer **lexer)
{
	return ((*lexer)->type == PIPE);
}
