/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/16 18:02:51 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	child(t_command *cmd, t_us *var, t_envp *envp, char **env)
{
	signal(SIGQUIT, hanld_siquit);
	if (var->k > 0) // not the first cmd
		dup2(var->fd[var->k - 1][0], 0);
	if (cmd->next != NULL)
		dup2(var->fd[var->k][1], 1);
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

void	wait_child(t_us *var)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < var->nb_cmd)
	{
		waitpid(var->pid[i], &(status), 0);
		if (WIFEXITED(status))
			var_globale.g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) == 1)
		{
			if (status == 131)
				write(2, "Quit (core dumped)\n", 19);
			else if (status == 2)
			{
				var_globale.g_exit_status = 130;
				write(2, "\n", 1);
			}
		}
		i++;
	}
	signal(SIGINT, handl_sigint);
	close_all(var);
	free_var(var);
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

void	execute_command(t_command *cmd, t_envp *envp, char **env)
{
	t_us		var;
	t_command	*tmp;

	if (var_and_single_built(cmd, &var, envp))
		return ;
	while (cmd != NULL) // other cmd
	{
		if (var.nb_cmd > 1 && var.k < var.nb_cmd - 1)
			if (pipe(var.fd[var.k]) == -1)
			{
				perror("error pipe");
				return ;
			}
		var.pid[var.k] = fork();
		if (var.pid[var.k] == 0)
			child(cmd, &var, envp, env);
		else
			perent(cmd, &var);
		tmp = cmd->next;
		cmd = tmp;
		var.k++;
	}
	wait_child(&var);
}
