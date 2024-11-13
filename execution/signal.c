/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:31:05 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/19 23:20:49 by oel-moue         ###   ########.fr       */
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

void	write_int(t_us *var)
{
	write(2, "\n", 1);
	g_var_globale.g_exit_status = 128 + SIGINT;
	var->signal_exit = 1;
}

void	write_quit(t_us *var)
{
	write(2, "Quit (core dumped)\n", 19);
	g_var_globale.g_exit_status = 128 + SIGQUIT;
	var->signal_exit = 1;
}
