/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:48:57 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:32:31 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_until_quote(t_args_for_remove_quotes *args)
{
	(*(args->i))++;
	while ((*(args->str))[*(args->i)]
		&& (*(args->str))[*(args->i)] != args->current_quote)
	{
		args->new_str[(*(args->j))++] = (*(args->str))[(*(args->i))++];
	}
	if ((*(args->str))[*(args->i)] == args->current_quote)
	{
		(*(args->i))++;
	}
}

char	*allocate_new_str(char *str)
{
	char	*new_str;

	new_str = (char *)gc_malloc(strlen(str) + 1);
	if (new_str == NULL)
	{
		return (NULL);
	}
	return (new_str);
}

void	remove_quotes_from_str(char **str, char *new_str)
{
	int							i;
	int							j;
	t_args_for_remove_quotes	args;

	i = 0;
	j = 0;
	args.str = str;
	args.new_str = new_str;
	args.i = &i;
	args.j = &j;
	args.current_quote = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			args.current_quote = (*str)[i];
			copy_until_quote(&args);
		}
		else
		{
			new_str[j++] = (*str)[i++];
		}
	}
	new_str[j] = '\0';
}

void	remove_quotes(char **str)
{
	char	*new_str;

	new_str = allocate_new_str(*str);
	if (new_str == NULL)
	{
		return ;
	}
	remove_quotes_from_str(str, new_str);
	gc_remove_ptr(*str);
	*str = new_str;
}

void	process_command_chain_and_files(t_command *command)
{
	int		i;
	t_file	*file;

	while (command)
	{
		i = 0;
		if (command->command_chain != NULL)
		{
			while (command->command_chain[i] != NULL)
			{
				remove_quotes(&command->command_chain[i]);
				i++;
			}
		}
		file = command->file;
		while (file)
		{
			remove_quotes(&file->file_name);
			file = file->next;
		}
		command = command->next;
	}
}
