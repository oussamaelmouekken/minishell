/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/20 12:01:36 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_cmd_builting(t_us *var, t_command *cmd, t_envp *envp)
{
	int	out;
	int	in;

	out = dup(1);
	in = dup(0);
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
	{
		restore_in_out(in, out);
		return ;
	}
	exe_builtins(cmd, &envp);
	restore_in_out(in, out);
}

void	child(t_command *cmd, t_us *var, t_envp *envp, char **env)
{
	signal(SIGQUIT, hanld_siquit);
	if (var->k > 0)
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
	{
		gc_free_all();
		exit(1);
	}
	exe(cmd, &envp, env);
}

void	wait_child(t_us *var)
{
	int	i;
	int	status;

	var->signal_exit = 0;
	status = 0;
	i = 0;
	while (i < var->nb_cmd)
	{
		waitpid(var->pid[i], &(status), 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
			{
				write_quit(var);
				break ;
			}
			else if (WTERMSIG(status) == SIGINT)
				write_int(var);
		}
		else if (WIFEXITED(status) && !var->signal_exit)
			g_var_globale.g_exit_status = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, handl_sigint);
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

void	execute_command(t_command *cmd, t_envp *envp, char **env)
{
	t_us		var;
	t_command	*tmp;

	if (var_and_single_built(cmd, &var, envp))
		return ;
	while (cmd != NULL)
	{
		if (var.nb_cmd > 1 && var.k < var.nb_cmd - 1)
		{
			if (pipe(var.fd[var.k]) == -1)
			{
				perror("error pipe");
				return ;
			}
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
