/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_phase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:29:47 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:06:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_file(t_file **file, t_file *new_file)
{
	t_file	*current;

	if (*file == NULL)
		*file = new_file;
	else
	{
		current = *file;
		while (current->next != NULL)
			current = current->next;
		current->next = new_file;
	}
}

t_file	*add_file_to_list(t_file **file, char *file_name,
		enum e_token_type file_type)
{
	t_file	*new_file;

	new_file = (t_file *)gc_malloc(sizeof(t_file));
	if (new_file == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	if (file_type != REDIRECT_INPUT)
		file_name = expansion(file_name);
	new_file->file_name = ft_strdup(file_name);
	new_file->file_type = file_type;
	if (file_type == REDIRECT_INPUT && (ft_strchr(file_name, '\'')
			|| ft_strchr(file_name, '"')))
		new_file->is_quoted = true;
	else
		new_file->is_quoted = false;
	if (file_name[0] == '\0' || count_words(file_name) > 1)
		new_file->is_ambiguous = true;
	else
		new_file->is_ambiguous = false;
	new_file->next = NULL;
	append_file(file, new_file);
	return (*file);
}

t_command	*add_command_to_list(t_command **list_of_commands, char **cmd_chain,
		t_file **file)
{
	t_command	*new_command;
	t_command	*current;

	new_command = (t_command *)gc_malloc(sizeof(t_command));
	if (new_command == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_command->command_chain = cmd_chain;
	new_command->file = *file;
	new_command->next = NULL;
	if (*list_of_commands == NULL)
		*list_of_commands = new_command;
	else
	{
		current = *list_of_commands;
		while (current->next != NULL)
			current = current->next;
		current->next = new_command;
	}
	return (*list_of_commands);
}

void	process_lexer_token(t_lexer *lexer, char ***cmd_chain, t_file **file)
{
	if (lexer->type == WORD && lexer->prev == NULL)
		*cmd_chain = add_cmd_chain_to_list(*cmd_chain, lexer->value);
	else if (lexer->type == WORD && lexer->prev->type == REDIRECT_IN)
		*file = add_file_to_list(file, lexer->value, REDIRECT_IN);
	else if (lexer->type == WORD && lexer->prev->type == REDIRECT_OUT)
		*file = add_file_to_list(file, lexer->value, REDIRECT_OUT);
	else if (lexer->type == WORD && lexer->prev->type == REDIRECT_APPEND)
		*file = add_file_to_list(file, lexer->value, REDIRECT_APPEND);
	else if (lexer->type == WORD && lexer->prev->type == REDIRECT_INPUT)
		*file = add_file_to_list(file, lexer->value, REDIRECT_INPUT);
	else if (lexer->type == WORD)
		*cmd_chain = add_cmd_chain_to_list(*cmd_chain, lexer->value);
}

t_command	*parser_phase(t_lexer *lexer)
{
	t_command	*list_of_commands;
	t_file		*file;
	char		**cmd_chain;

	list_of_commands = NULL;
	file = NULL;
	cmd_chain = NULL;
	while (lexer)
	{
		process_lexer_token(lexer, &cmd_chain, &file);
		if (lexer->type == PIPE)
		{
			list_of_commands = add_command_to_list(&list_of_commands, cmd_chain,
					&file);
			cmd_chain = NULL;
			file = NULL;
		}
		lexer = lexer->next;
	}
	list_of_commands = add_command_to_list(&list_of_commands, cmd_chain, &file);
	process_command_chain_and_files(list_of_commands);
	return (list_of_commands);
}
