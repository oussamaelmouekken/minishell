/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:20 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 13:32:07 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_var_globale;

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
	(void)list_envp;
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
	expansion_phase(lexer);
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
			write_and_free(input);
			break ;
		}
		if (handl(input, list_envp, lexer) == 1)
			continue ;
		command = parser_phase(*lexer);
		g_var_globale.env_arr = add_env_arr(list_envp);
		if (*input != '\0')
			add_history(input);
		if (*input == '\0')
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
	minishell_process(&lexer, env);
	gc_free_all();
	return (0);
}
