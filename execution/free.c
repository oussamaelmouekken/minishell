/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:52 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/13 19:59:32 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_in_child(t_global *var_globale)
{
	free_command_list(var_globale->cmd);
	free_envp(var_globale->envp);
	free_double(var_globale->env);
	free_var(var_globale->var);
	// rl_clear_history();
}

void	free_all_in_perent(t_global var_globale)
{
	free_envp(var_globale.envp);
	free_var(var_globale.var);
	rl_clear_history();
}

void	free_envp(t_envp *env)
{
	t_envp	*tmp;
	t_envp	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	env = NULL;
}

/////////////////////////

void	free_command(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->command_chain[i] != NULL)
	{
		free(cmd->command_chain[i]);
		i++;
	}
	free(cmd->command_chain);
	if (cmd->file != NULL)
	{
		free_file_list(cmd->file);
	}
	free(cmd);
}

void	free_file_list(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		tmp = file;
		file = file->next;
		free(tmp->file_name); // Free the file name string
		free(tmp);            // Free the t_file structure node
	}
}

void	free_command_list(t_command *cmd)
{
	t_command	*next;
	int			i;

	while (cmd != NULL)
	{
		next = cmd->next;
		if (cmd->command_chain != NULL)
		{
			i = 0;
			while (cmd->command_chain[i] != NULL)
			{
				free(cmd->command_chain[i]);
				i++;
			}
			free(cmd->command_chain);
			if (cmd->file != NULL)
			{
				free_file_list(cmd->file);
			}
			free(cmd);
		}
		cmd = next;
	}
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_var(t_us *var)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	if(var->fd == NULL)
		return ;
	if (var->fd != NULL)
	{
		while (i < var->nb_cmd - 1)
		{
			free(var->fd[i]);
			var->fd[i] = NULL;
			i++;
		}
		free(var->fd);
		var->fd = NULL;
	}
	if (var->pid)
	{
		free(var->pid);
		var->pid = NULL;
	}
}
