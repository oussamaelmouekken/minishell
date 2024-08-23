/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/24 00:49:29 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	f1;
// 	int	f2;

// 	f1 = open(av[1], O_RDWR | O_CREAT, 0644);
// 	f2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (ac == 0)
// 	{
// 		printf("Error: command found\n");
// 		return (1);
// 	}
// 	//pip_all(f1, f2, ac, av, env);

// int	count_arg(int ac)
// {
// 	int	i;
// 	int	count;

// 	count = 0;
// 	i = 2;
// 	while (i < ac - 1)
// 	{
// 		count++;
// 		i++;
// 	}
// 	return (count);
// }

void	exe_builtins(t_command *cmd, t_envp **envp)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0)
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
	{
		afficher_env(cmd, *envp);
	}
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0
		&& cmd->command_chain[1] == NULL)
	{
		pwd();
	}
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		cd(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		echo_n(cmd);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		unset(cmd, envp);
	//
	return ;
}
void	exe(t_command *cmd, t_envp **envp, char **env)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0)
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
	{
		afficher_env(cmd, *envp);
	}
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0
		&& cmd->command_chain[1] == NULL)
	{
		pwd();
	}
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		cd(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		echo_n(cmd);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		unset(cmd, envp);
	else
	{
		execute_cmd(cmd, env);
	}
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

// void	execute_command(t_command *cmd, t_envp *envp, char **env)
// {
// 	int	fd_in;
// 	int	fd_out;
// 	int	nb;
// 	nb = nbr_cmd(cmd);
// 	int	fd[nb - 1][2];
// 	int	out;
// 	int	pid[nb];
// 	int	i;

// 	if (nb <= 0)
// 		return ;
// 	i = 0;
// 	if (env == NULL)
// 		return ;
// 	fd_in = 0; // For the first command, input is from stdin
// 	if (is_builtins(cmd) && nb == 1)
// 	{
// 		out = dup(1);
// 		fd_in = infile(cmd);
// 		if (fd_in > 0)
// 		{
// 			dup2(fd_in, 0);
// 			close(fd_in);
// 		}
// 		fd_out = outfile(cmd);
// 		if (fd_out > 0)
// 		{
// 			dup2(fd_out, 1);
// 			close(fd_out);
// 		}
// 		if (fd_in < 0 || fd_out < 0)
// 			exit(1);
// 		exe_builtins(cmd, &envp);
// 		if (fd_in != 0)
// 			close(fd_in);
// 		dup2(out, 1);
// 		close(out);
// 	}
// 	else
// 	{
// 		while (cmd && i < nb)
// 		{
// 			if (cmd->next != NULL)
// 			{
// 				if (pipe(fd[i]) == -1)
// 				{
// 					perror("pipe error");		close(var->fd_in);

// 			{
// 				perror("fork error");
// 				return ;
// 			}
// 			else if (pid[i] == 0)
// 			{ // Child process
// 				if (fd_in != 0)
// 				{
// 					dup2(fd_in, 0);
// 					close(fd_in);
// 				}
// 				if (cmd->next != NULL)
// 				{
// 					dup2(fd[i][1], 1);
// 					close(fd[i][1]);
// 				}
// 				close(fd[i][0]);
// 				// Close all pipe ends in the child process
// 				fd_in = infile(cmd);
// 				if (fd_in > 0)
// 				{
// 					dup2(fd_in, 0);
// 					close(fd_in);
// 				}
// 				fd_out = outfile(cmd);
// 				if (fd_out > 0)
// 				{
// 					dup2(fd_out, 1);
// 					close(fd_out);
// 				}
// 				if (fd_in < 0 || fd_out < 0)
// 					exit(1);
// 				exe(cmd, &envp, env);
// 			}
// 			else
// 			{ // Parent process
// 				//while()
// 				if (fd_in != 0)
// 				{
// 					close(fd_in);
// 				}
// 				if (cmd->next != NULL)
// 				{
// 					close(fd[i][1]);
// 					fd_in = fd[i][0];
// 				}
// 			}
// 			cmd = cmd->next;
// 			i++;
// 		}
// 		i = 0;
// 		while(i < nb - 1)
// 		{
// 			close(fd[i][0]);
// 			close(fd[i][1]);
// 			i++;
// 		}
// 		i = 0;
// 		while (i < nb)
// 		{
// 				waitpid(pid[i], NULL, 0);
// 				i++;
// 		}
// 		// Close remaining file descriptors in the parent process
// 	}
// }

int	check_file(int fd)
{
	if (fd < 0)
	{
		perror("open file");
		return (0);
	}
	return (1);
}

int	infile(t_command *cmd)
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
		file = file->next;
	}
	return (fd_out);
}
int	is_builtins(t_command *cmd)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0)
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
	{
		return (1);
	}
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0
		&& cmd->command_chain[1] == NULL)
	{
		return (1);
	}
	else if (ft_cmp(cmd->command_chain[0], "cd") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "echo") == 0)
		return (1);
	else if (ft_cmp(cmd->command_chain[0], "unset") == 0)
		return (1);
	return (0);
}
int	nbr_cmd(t_command *cmd)
{
	int	i;

	i = 0;
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
	var->fd_in = infile(cmd);
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
	var->fd_in = infile(cmd);
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
	(void)i;
	if(cmd == NULL)
	 return;
	if (cmd->next != NULL)
	{
		close(var->fd[i][1]); // Parent closes the write end of the current pipe
	}
}
void	wait_child(t_us *var)
{
	int	i;

	i = 0;
	while (i < var->nb_cmd)
	{
		waitpid(var->pid[i], NULL, 0);
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
	var->fd_out = 1;
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
			pipe(var->fd[i]);///// bash ithlo kamlin bash close ikhdm hntach tanklosi kolchi 
			i++;
		}
	}
}
void	execute_command(t_command *cmd, t_envp *envp, char **env)
{
	t_us	var;

	var_use(cmd, &var);
	if (is_builtins(cmd) && var.nb_cmd == 1) // simple cmd
	{
		single_cmd(&var, cmd, envp);
		return ;
	}
	while (cmd != NULL) // other cmd
	{
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
