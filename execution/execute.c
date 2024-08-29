/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/29 08:51:23 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_builtins(t_command *cmd, t_envp **envp)
{
	if (ft_cmp(cmd->command_chain[0], "env") == 0
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
	{
		afficher_env(cmd, *envp);
	}
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0)
		pwd();
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		cd(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		echo_n(cmd);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		unset(cmd, envp);
	else if (ft_cmp(cmd->command_chain[0], "exit") == 0)
		my_exit();
	return ;
}
void	exe(t_command *cmd, t_envp **envp, char **env)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0
			&& cmd->command_chain[1] == NULL) || (ft_cmp(cmd->command_chain[0],
				"export") == 0))
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
		my_exit();
	if ((ft_cmp(cmd->command_chain[0], "env") == 0
			&& cmd->command_chain[1] != NULL))
	{
		printf("env with not arg or options\n");
		exit(1);
	}
	else
		execute_cmd(cmd, env);
	exit(1);
}

char	**Path_env(char **env)
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

	path = Path_env(env);
	i = 0;
	cmd_with_slash = ft_strjoin("/", cmd);
	while (path[i])
	{
		j = ft_strjoin(path[i], cmd_with_slash);
		if (access(j, F_OK | X_OK) == 0)
		{
			free(cmd_with_slash);
			free(path);
			return (j);
		}
		i++;
		free(j);
	}
	free(cmd_with_slash);
	free(path);
	return (NULL);
}

void	execute_cmd(t_command *cmd, char **env)
{
	char	*path;

	// check relative and absolute path
	if (access(cmd->command_chain[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd->command_chain[0], cmd->command_chain, env) == -1)
		{
			perror("execve error");
			return ;
		}
	}
	path = true_path(cmd->command_chain[0], env);
	if (path == NULL)
	{
		printf("error access \n");
		return ;
	}
	if (execve(path, cmd->command_chain, env) == -1)
	{
		perror("execve error");
	}
}

int	check_file(int fd)
{
	if (fd < 0)
	{
		perror("open file");
		return (0);
	}
	return (1);
}

int	infile(t_command *cmd, t_us *var)
{
	t_file	*file;
	int		fd_in;

	fd_in = 0;
	file = cmd->file;
	while (file != NULL)
	{
		if (file->file_type == REDIRECT_IN)
		{
			fd_in = open(file->file_name, O_RDONLY);
			if (check_file(fd_in) == 0)
				return (-1);
		}
		else if (file->file_type == REDIRECT_INPUT)
			fd_in = var->fd_herdoc;
		file = file->next;
	}
	return (fd_in);
}

int	outfile(t_command *cmd)
{
	t_file	*file;
	int		fd_out;

	fd_out = 0;
	file = cmd->file;
	while (file != NULL)
	{
		if (file->file_type == REDIRECT_OUT)
		{
			fd_out = open(file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
			if (check_file(fd_out) == 0)
				return (-1);
		}
		else if (file->file_type == REDIRECT_APPEND)
		{
			fd_out = open(file->file_name, O_RDWR | O_CREAT | O_APPEND, 0664);
			if (check_file(fd_out) == 0)
				return (-1);
		}
		file = file->next;
	}
	return (fd_out);
}

int	is_builtins(t_command *cmd)
{
	if (cmd->command_chain == NULL)
		return (0);
	if ((ft_cmp(cmd->command_chain[0], "env") == 0
			&& cmd->command_chain[1] == NULL) || (ft_cmp(cmd->command_chain[0],
				"export") == 0))
	{
		return (1);
	}
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
int	nbr_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
void	single_cmd(t_us *var, t_command *cmd, t_envp *envp)
{
	int	out;

	out = dup(1);
	var->fd_in = infile(cmd, var);
	if (var->fd_in > 0)
	{
		dup2(var->fd_in, 0);
		close(var->fd_in);
	}
	var->fd_out = outfile(cmd);
	if (var->fd_out > 0)
	{
		dup2(var->fd_out, 1);
		close(var->fd_out);
	}
	if (var->fd_in < 0 || var->fd_out < 0)
		exit(1);
	exe_builtins(cmd, &envp);
	if (var->fd_in != 0)
		close(var->fd_in);
	dup2(out, 1);
	close(out);
}
void	child(t_command *cmd, t_us *var, t_envp *envp, char **env, int i)
{
	if (i > 0) // not the first cmd
		dup2(var->fd[i - 1][0], 0);
	if (cmd->next != NULL)
		dup2(var->fd[i][1], 1);
	close_all(var);
	var->fd_in = infile(cmd, var);
	if (var->fd_in > 0)
	{
		dup2(var->fd_in, 0);
		close(var->fd_in);
	}
	var->fd_out = outfile(cmd);
	if (var->fd_out > 0)
	{
		dup2(var->fd_out, 1);
		close(var->fd_out);
	}
	if (var->fd_in < 0 || var->fd_out < 0)
		exit(1);
	exe(cmd, &envp, env);
}
void	perent(t_us *var, t_command *cmd, int i)
{
	if (i > 0)
	{
		close(var->fd[i - 1][0]);
		// Parent closes the read end of the previous pipe
	}
	if (cmd->next != NULL)
	{
		close(var->fd[i][1]); // Parent closes the write end of the current pipe
	}
}
void	wait_child(t_us *var)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < var->nb_cmd)
	{
		waitpid(var->pid[i], &status, 0);
		if (WIFEXITED(status) == 1)
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
	close_all(var);
}

void	close_all(t_us *var)
{
	int	i;

	i = 0;
	while (i < (var->nb_cmd - 1))
	{
		if (var->fd[i][0] != -1)
			close(var->fd[i][0]);
		if (var->fd[i][1] != -1)
			close(var->fd[i][1]);
		i++;
	}
}
void	var_use(t_command *cmd, t_us *var)
{
	int	i;

	i = 0;
	var->k = 0;
	var->fd_in = 0;
	var->fd_herdoc = 0;
	var->fd_out = 1;
	var->nbr_herdoc = count_herdoc(cmd);
	var->nb_cmd = nbr_cmd(cmd);
	if (var->nb_cmd == 1 && is_builtins(cmd) == 0)
		var->pid = malloc(sizeof(int) * var->nb_cmd);
	else if (var->nb_cmd > 1)
	{
		var->pid = malloc(sizeof(int) * var->nb_cmd);
		var->fd = malloc(sizeof(int *) * (var->nb_cmd - 1));
		i = 0;
		while (i < (var->nb_cmd - 1))
		{
			var->fd[i] = malloc(sizeof(int) * 2);
			pipe(var->fd[i]);
			///// bash ithlo kamlin bash close ikhdm hntach tanklosi kolchi
			i++;
		}
	}
}
int	var_use_and_herdoc(t_command *cmd, t_us *var)
{
	if (cmd == NULL)
		return (0);
	var_use(cmd, var);
	if (var->nbr_herdoc > 16)
	{
		printf("maximum here-document count exceeded\n");
		return (0);
	}
	if (var->nbr_herdoc >= 1)
		herdoc(cmd, var);
	return (1);
}
void	execute_command(t_command *cmd, t_envp *envp, char **env)
{
	t_us	var;

	if (var_use_and_herdoc(cmd, &var) == 0) // herdoc and use variable
		return ;
	if (var.nb_cmd == 1 && is_builtins(cmd)) // simple cmd is builtins or other
	{
		single_cmd(&var, cmd, envp);
		return ;
	}
	while (cmd != NULL) // other cmd
	{
		if (var.nb_cmd > 1)
			if (pipe(var.fd[var.k]) == -1 && var.k < var.nb_cmd - 1)
			{
				perror("error pipe");
				return ;
			}
		var.pid[var.k] = fork();
		if (var.pid[var.k] == 0)
			child(cmd, &var, envp, env, var.k);
		else
			perent(&var, cmd, var.k);
		cmd = cmd->next;
		var.k++;
	}
	wait_child(&var);
}
