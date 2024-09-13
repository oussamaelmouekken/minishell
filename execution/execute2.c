/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:49:17 by oussama           #+#    #+#             */
/*   Updated: 2024/09/12 18:51:15 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file(int fd)
{
	if (fd < 0)
	{
		perror("minishell error");
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
		if (file->is_ambiguous == true)
		{
			write(2, "minishell: ", 11);
			write(2, file->file_name, ft_strlen(file->file_name));
			write(2, ": ambiguous redirect\n", 21);
			return (-1);
		}
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
		if (file->is_ambiguous == true)
		{
			write(2, "minishell: ", 11);
			write(2, file->file_name, ft_strlen(file->file_name));
			write(2, ": ambiguous redirect\n", 21);
			return (-1);
		}
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
void	execute_cmd(t_command *cmd, char **env)
{
	char	*path;

	if (access(cmd->command_chain[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd->command_chain[0], cmd->command_chain, env) == -1)
		{
			perror("command not found");
			exit(127);
		}
	}
	path = true_path(cmd->command_chain[0], env);
	if (path == NULL)
	{
		perror("path not found");
		exit(127);
	}
	if (execve(path, cmd->command_chain, env) == -1)
	{
		perror("command not found");
		exit(127);
	}
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