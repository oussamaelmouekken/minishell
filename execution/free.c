/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:14:28 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/19 14:29:17 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_herdoc(t_command *cmd)
{
	t_file	*f;
	int		i;

	i = 0;
	while (cmd)
	{
		f = cmd->file;
		while (f != NULL)
		{
			if (f->file_type == REDIRECT_INPUT)
				i++;
			f = f->next;
		}
		cmd = cmd->next;
	}
	return (i);
}

void	write_ambiguous(t_file *file)
{
	write(2, "minishell: ", 11);
	write(2, file->file_name, ft_strlen(file->file_name));
	write(2, ": ambiguous redirect\n", 21);
	g_var_globale.g_exit_status = 1;
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		gc_remove_ptr(str[i]);
		i++;
	}
	gc_remove_ptr(str);
}

void	free_file_list(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		tmp = file;
		file = file->next;
		gc_remove_ptr(tmp->file_name);
		gc_remove_ptr(tmp);
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
				gc_remove_ptr(cmd->command_chain[i]);
				i++;
			}
			gc_remove_ptr(cmd->command_chain);
			if (cmd->file != NULL)
			{
				free_file_list(cmd->file);
			}
			gc_remove_ptr(cmd);
		}
		cmd = next;
	}
}
