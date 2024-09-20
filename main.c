/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:20 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/20 15:35:16 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_var_globale;

// void    show_command(t_command *command)
// {
//     t_command    *current;
//     t_file        *file;
//     int            i;
//     int            j;

//     current = command;
//     j = 0;
//     char *e_token_type[6] = {
//         "PIPE",            // = |
//         "REDIRECT_OUT",    // = >
//         "REDIRECT_IN",     // = <
//         "REDIRECT_APPEND", // = >>
//         "REDIRECT_INPUT",  //= <<
//         "WORD",
//     };
//     char *is_ambiguous[2] = {
//         "false",
//         "true",
//     };
//     char *is_quoted[2] = {
//         "false",
//         "true",
//     };
//     while (current != NULL)
//     {
//         i = 0;
//         if (current->command_chain != NULL)
//             while (current->command_chain[i] != NULL)
//             {
//                 printf("arr[%i]: %s, ", i, current->command_chain[i]);
//                 i++;
//             }
//         printf("\n");
//         file = current->file;
//         while (file != NULL)
//         {
//     printf("filename : `%s` filetype : `%s`  is_ambiguous `%s` is_quoted `%s`\n",
//                 file->file_name, e_token_type[file->file_type],
//                 is_ambiguous[file->is_ambiguous], is_quoted[file->is_quoted]);
//             file = file->next;
//         }
//         current = current->next;
//         printf("\n");
//         j++;
//     }
// }
void	print_minishell(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗");
	printf("██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██");
	printf("║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\n");
}

int	handl(char *input, t_envp *list_envp, t_lexer **lexer)
{
	if (check_for_closed_quotes(input) == 0)
	{
		g_var_globale.g_exit_status = 2;
		write(2, "minishell: syntax error\n", 24);
		free(input);
		return (1);
	}
	input = add_spaces_around_special_chars(input);
	if (input == NULL)
	{
		write(2, "minishell: syntax error\n", 24);
		g_var_globale.g_exit_status = 2;
		free(input);
		return (1);
	}
	lexer_phase(lexer, input);
	expansion_phase(lexer, list_envp);
	if (syntax_error(*lexer))
	{
		g_var_globale.g_exit_status = 2;
		free_lexer_list(lexer);
		return (1);
	}
	return (0);
}

void	minishell_process(t_lexer **lexer, t_envp *list_envp)
{
	char		*input;
	t_command	*command;

	command = NULL;
	while (1)
	{
		input = readline(G_TTY "minishell$ " RESET);
		if (!input)
		{
			write(2, "exit\n", 5);
			free(input);
			break ;
		}
		if (handl(input, list_envp, lexer) == 1)
			continue ;
		command = parser_phase(*lexer);
		if(command != NULL && *input != '\0')
			add_history(input);
		if (command == NULL)
			continue ;
		else
			execute_command(command, list_envp, g_var_globale.env_arr);
		free_lexer_list(lexer);
		free_command_list(command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer	*lexer;
	t_envp	*env;

	env = NULL;
	lexer = NULL;
	g_var_globale.g_exit_status = 0;
	g_var_globale.env_arr = NULL;
	signal(SIGINT, handl_sigint);
	signal(SIGQUIT, SIG_IGN);
	print_minishell();
	if (argc != 1 || argv == NULL)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	env = add_env(envp);
	g_var_globale.size_list = size_of_list(env);
	g_var_globale.envp = env;
	g_var_globale.env_arr = add_env_arr(env);
	minishell_process(&lexer, env);
	gc_free_all();
	return (0);
}
