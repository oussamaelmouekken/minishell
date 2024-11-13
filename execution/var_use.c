/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_use.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:52:13 by oussama           #+#    #+#             */
/*   Updated: 2024/09/19 14:24:10 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	perent(t_command *cmd, t_us *var)
{
	signal(SIGINT, SIG_IGN);
	if (var->k > 0)
	{
		close(var->fd[var->k - 1][0]);
	}
	if (cmd->next != NULL)
	{
		close(var->fd[var->k][1]);
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
	var->pid = NULL;
	var->fd = NULL;
	var->nbr_herdoc = count_herdoc(cmd);
	var->nb_cmd = nbr_cmd(cmd);
	if (var->nb_cmd == 1 && is_builtins(cmd) == 0 && cmd->command_chain != NULL)
		var->pid = gc_malloc(sizeof(int) * var->nb_cmd);
	else if (var->nb_cmd > 1)
	{
		var->pid = gc_malloc(sizeof(int) * var->nb_cmd);
		var->fd = gc_malloc(sizeof(int *) * (var->nb_cmd - 1));
		i = 0;
		while (i < (var->nb_cmd - 1))
		{
			var->fd[i] = gc_malloc(sizeof(int) * 2);
			pipe(var->fd[i]);
			i++;
		}
	}
}

int	var_use_and_herdoc(t_command *cmd, t_us *var, t_envp *env)
{
	if (cmd->command_chain == NULL && cmd->file == NULL)
		return (0);
	var_use(cmd, var);
	g_var_globale.cmd = cmd;
	g_var_globale.envp = env;
	g_var_globale.var = var;
	if (var->nbr_herdoc > 16)
	{
		write(2, "max here-document count exceeded\n", 33);
		g_var_globale.g_exit_status = 2;
		gc_free_all();
		exit(2);
	}
	if (var->nbr_herdoc >= 1)
	{
		if (herdoc(cmd, var, env))
			return (0);
	}
	return (1);
}

int	var_and_single_built(t_command *cmd, t_us *var, t_envp *envp)
{
	g_var_globale.g_exit_status = 0;
	if (var_use_and_herdoc(cmd, var, envp) == 0)
	{
		return (1);
	}
	if (var->nb_cmd == 1 && is_builtins(cmd) == 1)
	{
		single_cmd_builting(var, cmd, envp);
		return (1);
	}
	if (cmd->command_chain == NULL && var->nb_cmd == 1)
	{
		var->fd_in = infile(cmd, var);
		var->fd_out = outfile(cmd);
		if (var->fd_in < 0 || var->fd_out < 0)
		{
			return (1);
		}
		return (1);
	}
	return (0);
}
