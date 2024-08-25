/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:38:19 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/25 18:57:12 by oel-moue         ###   ########.fr       */
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

void	herdoc(t_command *cmd, t_us *var)
{
	char	*str_line;
	t_file	*f;
	int		fd[2];

	while (cmd)
	{
		f = cmd->file;
		while (f)
		{
			if (f->file_type == REDIRECT_INPUT)
			{
				pipe(fd);
				while ((str_line = readline("> ")) != NULL)
				{
					if (ft_cmp(str_line, f->file_name) == 0)
					{
						free(str_line);
						break ;
					}
					str_line = ft_strjoin(str_line, "\n");
					write(fd[1], str_line, ft_strlen(str_line));
				    free(str_line);
				}
			}
            var->fd_herdoc = fd[0];
            close(fd[1]);
			f = f->next;
		}
		cmd = cmd->next;
	}
}
