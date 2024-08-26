/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:20 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/26 16:17:05 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_minishell(void)
// {
// 	printf("\n");
// 	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
// 	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
// 	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
// 	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
// 	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
// 	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
// 	printf("\n");
// }

void show_command(t_command *command)
{
	t_command *current;
	t_file *file;
	int i;
	int j;

	current = command;
	j = 0;
	char *token_type[6] = {
		"PIPE",			   // = |
		"REDIRECT_OUT",	   // = >
		"REDIRECT_IN",	   // = <
		"REDIRECT_APPEND", // = >>
		"REDIRECT_INPUT",  //= <<
		"WORD",
	};
	char *is_ambiguous[2] = {
		"false",
		"true",
	};
	char *is_quoted[2] = {
		"false",
		"true",
	};
	while (current != NULL)
	{
		i = 0;
		printf("command-%i:\n", j + 1);
		if (current->command_chain != NULL)
			while (current->command_chain[i] != NULL)
			{
				printf("arr[%i]: %s, ", i, current->command_chain[i]);
				i++;
			}
		printf("\n");
		file = current->file;
		while (file != NULL)
		{
			printf("filename : `%s` filetype : `%s`  is_ambiguous `%s` is_quoted `%s`\n", file->file_name,
				   token_type[file->file_type], is_ambiguous[file->is_ambiguous], is_quoted[file->is_quoted]);
			file = file->next;
		}
		current = current->next;
		printf("\n");
		j++;
	}
}

void minishell_process(t_lexer **lexer, t_envp *list_envp)
{
	char *input;
	t_command *command;
	char **env;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		add_history(input);
		if (check_for_closed_quotes(input) == 0)
		{
			printf("Syntax Error: quotes are not closed\n");
			free(input);
			continue;
		}
		input = add_spaces_around_special_chars(input);
		if (input == NULL)
		{
			printf("Syntax Error\n");
			free(input);
			continue;
		}
		lexer_phase(lexer, input);
		expansion_phase(lexer, list_envp);
		// if (syntax_error(*lexer))
		// {
		// 	free_list(lexer);
		// 	free(input);
		// 	continue ;
		// }
		command = parser_phase(*lexer);
		env = add_env_arr(list_envp);
        execute_command(command, list_envp,env);
		// for debugging
		//show_command(command);
		free_lexer_list(lexer);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer	*lexer;
	t_envp	*env;

	lexer = NULL;
	if (argc != 1 || argv == NULL)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	env = add_env(envp);
	minishell_process(&lexer, env);
	return (0);
}
