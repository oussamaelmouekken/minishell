/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:20 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/13 20:02:39 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	var_globale;

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

void	show_command(t_command *command)
{
	t_command	*current;
	t_file		*file;
	int			i;
	int			j;

	current = command;
	j = 0;
	char *token_type[6] = {
		"PIPE",            // = |
		"REDIRECT_OUT",    // = >
		"REDIRECT_IN",     // = <
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
			printf("filename : `%s` filetype : `%s`  is_ambiguous `%s` is_quoted `%s`\n",
				file->file_name, token_type[file->file_type],
				is_ambiguous[file->is_ambiguous], is_quoted[file->is_quoted]);
			file = file->next;
		}
		current = current->next;
		printf("\n");
		j++;
	}
}

void	minishell_process(t_lexer **lexer, t_envp *list_envp)
{
	char		*input;
	t_command	*command;

	command = NULL;
	var_globale.env = NULL;
	while (1)
	{
		input = readline(G_tty "minishell$ " RESET);
		if (!input)
		{
			write(2, "exit\n", 5);
			free(input);
			break ;
		}
		add_history(input);
		if (check_for_closed_quotes(input) == 0)
		{
			var_globale.g_exit_status = 2;
			write(2, "minishell: syntax error\n", 24);
			free(input);
			continue ;
		}
		input = add_spaces_around_special_chars(input);
		if (input == NULL)
		{
			write(2, "minishell: syntax error\n", 24);
			var_globale.g_exit_status = 2;
			free(input);
			continue ;
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
		if (command == NULL) // ila kant ./minishell bla cmd
			continue ;
		else
		{
			var_globale.env = add_env_arr(list_envp);
			execute_command(command, list_envp, var_globale.env);
			// for debugging
			// show_command(command);
			free_double(var_globale.env);
		}
		free_lexer_list(lexer);
		free_command_list(var_globale.cmd);
		free(input);
		printf("exit %d\n",var_globale.g_exit_status);
	}
}

void	change_shlvl(t_envp **envp)
{
	char	*v;
	int		nbr_shlvl;
	t_envp	*tmp;

	tmp = *envp;
	while (envp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			nbr_shlvl = ft_atoi(tmp->value) + 1;
			if (nbr_shlvl >= 100)
			{
				write(2, "warning: shell level (100) too high\n", 36);
				nbr_shlvl = 1;
			}
			free(tmp->value);
			v = ft_itoa(nbr_shlvl);
			tmp->value = ft_strdup(v);
			free(v);
			return ;
		}
		tmp = tmp->next;
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_lexer	*lexer;
	t_envp	*env;

	env = NULL;
	lexer = NULL;
	var_globale.g_exit_status = 0;
	signal(SIGINT, handl_sigint);
	signal(SIGQUIT, SIG_IGN); // ignore in perent process
	if (argc != 1 || argv == NULL)
	{
		printf("This program does not accept arguments\n");
		exit(0);
	}
	env = add_env(envp);
	var_globale.envp = env;
	minishell_process(&lexer, env);
	// free_all_in_perent(var_globale);
	return (0);
}
