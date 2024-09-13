/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:31:05 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/12 16:03:09 by oussama          ###   ########.fr       */
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
	var_globale.g_exit_status = 130;
}

void	handl_sigint_herdoc(int sig)
{
	(void)sig;
	var_globale.g_exit_status = 130;
	exit(130);
}

void	hanld_siquit(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_DFL);
    exit(131);
}

