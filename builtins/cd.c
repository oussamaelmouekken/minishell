/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:49:09 by oussama           #+#    #+#             */
/*   Updated: 2024/08/25 19:48:46 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_old_new_pwd(t_envp *env,char newpwd[4096], char oldpwd[4096])
{
	t_envp	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, "OLDPWD=", 7) == 0)
		{
			tmp->value = ft_strdup(oldpwd);
			if(tmp->value == NULL)
			{
				perror("error malloc()");
				return ;
			}
		}
		if (ft_strncmp(tmp->key, "PWD=", 4) == 0)
		{
			tmp->value = ft_strdup(newpwd);
			if(tmp->value == NULL)
			{
				perror("error malloc()");
				return ;
			}
		}
		tmp = tmp->next;
	}
	return;
}
char *ft_setenv(char *variable, t_envp *env)
{
	t_envp	*tmp;
	char	*my_env;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, variable, ft_strlen(variable)) == 0)
		{
			my_env = ft_strdup(tmp->value);
			if (my_env == NULL)
			{
				perror("error malloc()");
				return (NULL);
			}
			return (my_env);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
void	cd(t_command *cmd ,t_envp *env)
{
	char	oldpwd[4096];
	char	newpwd[4096];
	char	*path;

	if (cmd->command_chain[1] == NULL)
	{
		path = ft_setenv("HOME", env);
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			return;
		}
	}
	else
		path = cmd->command_chain[1];
	if (getcwd(oldpwd, 4096) == NULL)
	{
		perror("error getcwd()");
		return ;
	}
	if (chdir(path) == -1)
	{
		perror("error chdir()");
		return ;
	}
	if (getcwd(newpwd, 4096) == NULL)
	{
		perror("error getcwd()");
		return ;
	}
	change_old_new_pwd(env, newpwd, oldpwd);
	//free(split_line);
}
