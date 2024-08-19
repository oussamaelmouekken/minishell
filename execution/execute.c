/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/19 22:40:12 by oel-moue         ###   ########.fr       */
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

void	exe(t_command *cmd, t_envp **envp,char **env)
{
	if ((ft_cmp(cmd->command_chain[0], "env") == 0)
		|| (ft_cmp(cmd->command_chain[0], "export") == 0))
		afficher_env(cmd, *envp);
	else if (ft_cmp(cmd->command_chain[0], "pwd") == 0
		&& cmd->command_chain[1] == NULL)
		{
			printf("hhhhhhhhh\n");
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

int	check_file(int fd)
{
	if (fd < 0)
	{
		perror("Error opening file");
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
			fd_in = open(file->file_name, O_RDONLY | O_CREAT);
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
			fd_out = open(file->file_name, O_RDWR | O_CREAT);
			if (check_file(fd_out) == 0)
				return (-1);
		}
		file = file->next;
	}
	return (fd_out);
}

void	execute_command(t_command *cmd, t_envp *envp, char **env)
{
	int	fd_in;
	int	fd_out;
	int	fd[2];
	int	pid;

	if (env == NULL)
		return ;
	fd_in = 0;
	while (cmd)
	{
		// Create a pipe if there is another command in the pipeline
		if (cmd->next != NULL)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			return ;
		}
		else if (pid == 0) // Child process
		{
			if (fd_in != 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (cmd->next != NULL)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			fd_in = infile(cmd);
			if (fd_in > 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			fd_out = outfile(cmd);
			if (fd_out > 0)
			{
				dup2(fd_out, 1);
				close(fd_out);
			}
			if (fd_in < 0 || fd_out < 0)
			{
				printf("error open\n");
				exit(1);
			}
			exe(cmd, &envp,env);
		}
		else // Parent process
		{
			wait(NULL);
			if (fd_in != 0)
				close(fd_in);
			if (cmd->next != NULL)
				close(fd[1]);
			fd_in = fd[0];
			cmd = cmd->next;
		}
	}
}
