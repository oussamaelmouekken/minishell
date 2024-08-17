/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:56:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/16 12:49:39 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(t_command *cmd, t_envp **env)
{
    if(*env == NULL)
     return;
    // // simple commande 
    // int fd[2];
    // pipe(fd);
    // int d = fork();
    // if(d == 0)
    // {

    // }
    // else 
    // {
        
    // }
    show_command(cmd);
}
