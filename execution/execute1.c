/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:31:10 by oussama           #+#    #+#             */
/*   Updated: 2024/09/20 00:50:48 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_builtins(t_command *cmd, t_envp **envp)
{
	if (ft_cmp(cmd->command_chain[0], "cd") == 0
		&& cmd->command_chain[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		g_var_globale.g_exit_status = 1;
	}
	else if ((ft_cmp(cmd->command_chain[0], "env") == 0
			&& cmd->command_chain[1] != NULL))
	{
		write(2, "env: invalid option\n", 20);
		g_var_globale.g_exit_status = 1;
	}
	else if (ft_cmp(cmd->command_chain[0], "env") == 0
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
		afficher_env(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0)
		pwd();
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		cd(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		echo_n(cmd);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		unset(cmd, envp);
	else if (ft_cmp(cmd->command_chain[0], "exit") == 0)
		my_exit(cmd);
}

void	exe(t_command *cmd, t_envp **envp, char **env)
{
	if (cmd->command_chain == NULL)
		return ;
	else if (is_builtins(cmd))
		exe_builtins(cmd, envp);
	else
		execute_cmd(cmd, env);
	gc_free_all();
	exit(g_var_globale.g_exit_status);
}

char	**path_env(char **env)
{
	int		i;
	char	*s1;
	char	**s;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	s1 = ft_strchr(env[i], '/');
	s = ft_split(s1, ':');
	return (s);
}

char	*true_path(char *cmd, char **env)
{
	char	**path;
	int		i;
	char	*j;
	char	*cmd_with_slash;

	path = path_env(env);
	if (path == NULL)
		return (NULL);
	i = 0;
	cmd_with_slash = ft_strjoin("/", cmd);
	while (path[i])
	{
		j = ft_strjoin(path[i], cmd_with_slash);
		if (access(j, F_OK | X_OK) == 0)
		{
			gc_remove_ptr(cmd_with_slash);
			free_double(path);
			return (j);
		}
		i++;
		gc_remove_ptr(j);
	}
	gc_remove_ptr(cmd_with_slash);
	free_double(path);
	return (NULL);
}

int	is_builtins(t_command *cmd)
{
	if (cmd->command_chain == NULL)
		return (0);
	else if (cmd->command_chain[0] == NULL)
		return (0);
	else if (ft_cmp(cmd->command_chain[0], "env") == 0
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "exit") == 0)
		return (1);
	return (0);
}
