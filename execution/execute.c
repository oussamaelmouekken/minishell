/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/17 22:04:08 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../minishell.h"

// void join_cmd(t_command *command)
// {
// 	t_command	*current;
// 	t_file		*file;
// 	int			i;
// 	int			j;

// 	current = command;
// 	j = 0;
// 	while (current != NULL)
// 	{
// 		i = 0;
// 		printf("command-%i: ", j + 1);
// 		while (current->command_chain[i] != NULL)
// 		{
// 			printf("arg[%i] = %s,", i, current->command_chain[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		char *token_type[6] = {
// 			"PIPE",            // = |
// 			"REDIRECT_OUT",    // = >
// 			"REDIRECT_IN",     // = <
// 			"REDIRECT_APPEND", // = >>
// 			"REDIRECT_INPUT",  //= <<
// 			"WORD",
// 		};
// 		file = current->file;
// 		while (file != NULL)
// 		{
// 			printf("filename : `%s` filetype : `%s`", file->file_name,
// 				token_type[file->file_type]);
// 			file = file->next;
// 		}
// 		current = current->next;
// 		printf("\n");
// 		j++;
// 	}
// }

// 	void	exe(char *line, char **av, t_env **env)
// {
// 	char	**cmd;

// 	cmd = ft_split(line, ' '); /// after parsing with linked list
// 	if (av == NULL)
// 		printf("errors\n");
// 	if ((ft_cmp(cmd[0], "env") == 0) || (ft_cmp(cmd[0], "export") == 0))
// 		afficher_env(cmd, *env);
// 	else if (ft_cmp(cmd[0], "pwd") == 0 && cmd[1] == NULL)
// 		pwd();
// 	else if (ft_cmp(cmd[0], "cd") == 0)
// 		cd(cmd, *env);
// 	else if (ft_cmp(cmd[0], "echo") == 0)
// 		echo_n(cmd);
// 	else if (ft_cmp(cmd[0], "unset") == 0)
// 		unset(cmd, env);
// 	// else if(commande_exucution(line) == 0)
// 	// {
// 	// }
// 	else
// 	{
// 		printf("Error: command found problem builtins\n");
// 		return ;
// 	}
// }
void	exe(t_command *cmd, t_envp**env)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0) || (ft_cmp(cmd->command_chain[0], "export") == 0))
		afficher_env(cmd, *env);
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0 && cmd->command_chain[1] == NULL)
		pwd();
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		cd(cmd, *env);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		echo_n(cmd);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		unset(cmd, env);
	// else if(commande_exucution(line) == 0)
	// {
	// }
	else
	{
		printf("Error: command found problem builtins\n");
		return ;
	}
}
void	execute_command(t_command *cmd, t_envp **env)
{
	// char	**args_cmd;
	if (*env == NULL)
		return ;
	// args_cmd = join_cmd(cmd);

	//printf("%s\n",cmd->command_chain[0]);
	// simple commande
	// int fd[2];
	// pipe(fd);
	// int d = fork();
	// if(d == 0)
	// {
	// }
	// else
	// {
	// }
	//char **split = ft_split(*cmd->command_chain[0],' ');
	//char *path = "/bin/ls";
	//execv(path,cmd->command_chain);
	//path = "/usr/bin/wc";
	//char **env; haka khas ykon;
	
	exe(cmd,env);
	//execve(path,cmd->command_chain);
	//cmd = cmd->next;
	//show_command(cmd);
}
