/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:38:19 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/01 19:42:31 by oel-moue         ###   ########.fr       */
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
int     wait_herdoc(int pid)
{
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
			g_exit_status = g_exit_status >> 8;
	if(g_exit_status == 130)
	{
		printf("\n");
		return 1;
	}
	return 0;
}
int 	loop_herdoc(t_us *var, t_file *f, t_envp *env)
{
	char	*str_line;
	int		fd[2];
	int		i;

	pipe(fd);
	i = fork();
	if (i == 0)
	{
		signal(SIGINT, handl_sigint_herdoc);
		close(fd[0]);
		while ((str_line = readline("> ")) != NULL)
		{
			if (ft_cmp(str_line, f->file_name) == 0)
			{
				free(str_line);
				break ;
			}
			str_line = ft_strjoin(str_line, "\n");
			if (f->is_quoted == false)
				str_line = expansion(str_line, env);
			write(fd[1], str_line, ft_strlen(str_line));
			free(str_line);
		}
		if (str_line == NULL)
		{
			printf("minshell: here-document  delimited by end-of-file (wanted `%s')\n", f->file_name);
			exit(1);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		var->fd_herdoc = fd[0];
		close(fd[1]);
		if(wait_herdoc(i))
			return 1;
	}
	return 0;
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
				if(loop_herdoc(var, f, env))
					return 1;
			}
			f = f->next;
		}
		cmd = cmd->next;
	}
	return 0;
}
