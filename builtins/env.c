/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:47:46 by oussama           #+#    #+#             */
/*   Updated: 2024/09/22 14:52:22 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_value_env(char *node, t_envp **env)
{
	t_envp	*tmp;
	t_envp	*new_node;
	int		f;

	f = 0;
	if (*env == NULL)
		f = 1;
	tmp = *env;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new_node = (t_envp *)gc_malloc(sizeof(t_envp));
	if (erro_malloc(new_node))
		return ;
	init_(new_node);
	if (check_if_egal_exit(node) == 0)
		new_node->egal_exist = true;
	new_node->key = to_egal(node);
	if ((ft_strcmp(new_node->key, "PATH=") == 0) && f == 1)
		new_node->env_path = true;
	new_node->value = to_fin(node);
	new_node->next = NULL;
	if (tmp)
		tmp->next = new_node;
	else
		*env = new_node;
}

void	env_egal_null(t_envp **env)
{
	char	*v1;
	char	*p;
	char	pwd[4096];

	v1 = "PATH=/nfs/homes/oel-moue/bin:/usr/local/sbin:/usr/local/bin:"
		"/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	ft_add_value_env(v1, env);
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		p = ft_strjoin("PWD=", pwd);
		ft_add_value_env(p, env);
		gc_remove_ptr(p);
	}
	else
	{
		perror("error getcwd()");
		return ;
	}
	ft_add_value_env("SHLVL=1", env);
	ft_add_value_env("_=/usr/bin/env", env);
}

t_envp	*add_env(char **env)
{
	t_envp	*envp;
	int		i;

	envp = NULL;
	if (*env == NULL)
		env_egal_null(&envp);
	else
	{
		i = 0;
		envp = (t_envp *)gc_malloc(sizeof(t_envp));
		if (envp == NULL)
		{
			printf("Error: gc_malloc \n");
			return (NULL);
		}
		envp->key = to_egal(env[i]);
		envp->value = to_fin(env[i]);
		envp->next = NULL;
		i++;
		while (env[i] != NULL)
			ft_add_value_env(env[i++], &envp);
	}
	change_shlvl(&envp);
	return (envp);
}

void	print_env_variable(t_envp *tmp, t_command *cmd)
{
	if (ft_strcmp(cmd->command_chain[0], "export") == 0
		&& cmd->command_chain[1] == NULL)
	{
		if (!(tmp->key[0] == '_' && tmp->key[1] == '='))
		{
			if (tmp->egal_exist == false)
				printf("declare -x %s\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s%s\n", tmp->key, tmp->value);
		}
	}
	else
	{
		if (tmp->egal_exist == false)
			printf("%s%s\n", tmp->key, tmp->value);
	}
}

void	afficher_env(t_command *cmd, t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	if (ft_strcmp(cmd->command_chain[0], "export") == 0
		&& cmd->command_chain[1] != NULL)
	{
		export(cmd, &env);
		return ;
	}
	while (tmp != NULL)
	{
		if (tmp->env_path == false)
		{
			if (ft_strcmp(cmd->command_chain[0], "export") == 0
				&& cmd->command_chain[1] == NULL)
			{
				sort_list(&env);
				check_egal(&env);
			}
			print_env_variable(tmp, cmd);
		}
		tmp = tmp->next;
	}
}
