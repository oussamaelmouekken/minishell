/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:38:19 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 01:19:33 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_herdoc(int pid)
{
	waitpid(pid, &(g_var_globale.g_exit_status), 0);
	if (WIFEXITED(g_var_globale.g_exit_status))
		g_var_globale.g_exit_status = g_var_globale.g_exit_status >> 8;
	if (g_var_globale.g_exit_status == 130)
	{
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

void	herdoc_error(t_file *f)
{
	write(2, "minshell: here-document  delimited by end-of-file ", 51);
	write(2, f->file_name, ft_strlen(f->file_name));
	write(2, "\n", 1);
	gc_free_all();
	exit(1);
}

void	herdoc1(t_file *f, t_envp *env, int f0, int f1)
{
	char	*str_line;

	(void)env;
	signal(SIGINT, handl_sigint_herdoc);
	close(f0);
	while (1)
	{
		str_line = readline(G_TTY "> " RESET);
		if (str_line == NULL)
			break ;
		if (ft_cmp(str_line, f->file_name) == 0)
		{
			free(str_line);
			break ;
		}
		str_line = ft_strjoin(str_line, "\n");
		if (f->is_quoted == false)
			str_line = expansion(str_line);
		write(f1, str_line, ft_strlen(str_line));
	}
	if (str_line == NULL)
		herdoc_error(f);
	close(f1);
	gc_free_all();
	exit(0);
}

int	loop_herdoc(t_us *var, t_file *f, t_envp *env)
{
	int	fd[2];
	int	i;

	pipe(fd);
	i = fork();
	if (i == 0)
	{
		herdoc1(f, env, fd[0], fd[1]);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		var->fd_herdoc = fd[0];
		close(fd[1]);
		if (wait_herdoc(i))
			return (1);
	}
	return (0);
}

int	herdoc(t_command *cmd, t_us *var, t_envp *env)
{
	t_file	*f;

	while (cmd)
	{
		f = cmd->file;
		while (f)
		{
			if (f->file_type == REDIRECT_INPUT)
			{
				if (loop_herdoc(var, f, env))
					return (1);
			}
			f = f->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
