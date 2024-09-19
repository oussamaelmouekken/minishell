/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:31:05 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/19 16:30:09 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handl_sigint(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var_globale.g_exit_status = 130;
}

void	handl_sigint_herdoc(int sig)
{
	(void)sig;
	g_var_globale.g_exit_status = 130;
	gc_free_all();
	exit(130);
}

void	hanld_siquit(int sig)
{
	(void)sig;
	gc_free_all();
	signal(SIGQUIT, SIG_DFL);
	exit(131);
}
