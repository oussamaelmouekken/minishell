/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:49:09 by oussama           #+#    #+#             */
/*   Updated: 2024/09/18 12:00:34 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(char *str)
{
	if (str == NULL)
	{
		perror("error gc_malloc()");
		return (1);
	}
	return (0);
}

void	change_old_new_pwd(t_envp *env, char newpwd[4096], char oldpwd[4096])
{
	t_envp	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, "OLDPWD=", 7) == 0)
		{
			gc_remove_ptr(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			if (error(tmp->value))
				return ;
		}
		if (ft_strncmp(tmp->key, "PWD=", 4) == 0)
		{
			gc_remove_ptr(tmp->value);
			tmp->value = ft_strdup(newpwd);
			if (error(tmp->value))
				return ;
		}
		tmp = tmp->next;
	}
	return ;
}

char	*ft_setenv(char *variable, t_envp *env)
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
				perror("error gc_malloc()");
				return (NULL);
			}
			return (my_env);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd2(char *path, char *oldpwd, char *newpwd)
{
	if (chdir(path) == -1)
	{
		gc_remove_ptr(path);
		gc_remove_ptr(oldpwd);
		perror("error chdir()");
		g_var_globale.g_exit_status = 1;
		return (1);
	}
	if (getcwd(newpwd, 4096) == NULL)
	{
		gc_remove_ptr(oldpwd);
		perror("error cd PWD");
		g_var_globale.g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	cd(t_command *cmd, t_envp *env)
{
	char	*oldpwd;
	char	newpwd[4096];
	char	*path;

	if (cmd->command_chain[1] == NULL)
	{
		path = ft_setenv("HOME", env);
		if (path == NULL)
		{
			gc_remove_ptr(path);
			write(2, "cd: HOME not set\n", 17);
			g_var_globale.g_exit_status = 1;
			return ;
		}
	}
	else
		path = cmd->command_chain[1];
	oldpwd = ft_setenv("PWD", env);
	if (cd2(path, oldpwd, newpwd))
		return ;
	gc_remove_ptr(path);
	change_old_new_pwd(env, newpwd, oldpwd);
	gc_remove_ptr(oldpwd);
}
