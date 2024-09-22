/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:49:17 by oussama           #+#    #+#             */
/*   Updated: 2024/09/22 01:45:14 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file(int fd, char *str)
{
	if (fd < 0)
	{
		write(2, str, ft_strlen(str));
		perror(" error ");
		g_var_globale.g_exit_status = 1;
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
			if (file->is_ambiguous == true)
			{
				write_ambiguous(file);
				return (-1);
			}
			fd_in = open(file->file_name, O_RDONLY);
			if (check_file(fd_in, file->file_name) == 0)
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
	int	f;

	f = 0;
	while (cmd->file != NULL)
	{
		if (write_ambiguous1(cmd->file) == -1)
			return (-1);
		else if (cmd->file->file_type == REDIRECT_OUT)
		{
			f = open(cmd->file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
			if (check_file(f, cmd->file->file_name) == 0)
				return (-1);
		}
		else if (cmd->file->file_type == REDIRECT_APPEND)
		{
			f = open(cmd->file->file_name, O_RDWR | O_CREAT | O_APPEND, 0664);
			if (check_file(f, cmd->file->file_name) == 0)
				return (-1);
		}
		cmd->file = cmd->file->next;
	}
	return (f);
}

void	error_e(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, " : command not found\n", 22);
	gc_free_all();
	exit(127);
}

void	execute_cmd(t_command *cmd, char **env)
{
	char	*path;

	if (cmd->command_chain[0] == NULL)
		return ;
	if (access(cmd->command_chain[0], F_OK) == 0)
	{
		if (execve(cmd->command_chain[0], cmd->command_chain, env) == -1)
		{
			if (access(cmd->command_chain[0], X_OK) == 0)
			{
				write(2, cmd->command_chain[0],
					ft_strlen(cmd->command_chain[0]));
				write(2, ": is a directory\n", 18);
				gc_free_all();
				exit(126);
			}
			error_e(cmd->command_chain[0]);
			exit(127);
		}
	}
	path = true_path(cmd->command_chain[0], env);
	if (path == NULL)
		error_e(cmd->command_chain[0]);
	if (execve(path, cmd->command_chain, env) == -1)
		error_e(cmd->command_chain[0]);
}
