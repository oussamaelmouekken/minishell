/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:47:46 by oussama           #+#    #+#             */
/*   Updated: 2024/08/25 19:50:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_envp *env, char *key)
{
	t_envp	*current;

    current = env;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}

char	*to_fin(char *str)
{
	int		i;
	int		j;
	char	*s;
	int		c;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	c = ft_strlen(str) - i;
	s = malloc(sizeof(char) * (c + 1));
	if (!s)
	{
		printf("error malloc\n");
		return (NULL);
	}
	j = 0;
	while (i < ft_strlen(str))
	{
		s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}
char	*to_egal(char *str)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
	{
		printf("error malloc\n");
		return (NULL);
	}
	j = 0;
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

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
	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (new_node == NULL)
	{
		printf("Error: Memory allocation failed\n");
		return ;
	}
	new_node->env_path = false;
	new_node->egal_exist = false;
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

	v1 = "PATH=/nfs/homes/oel-moue/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	ft_add_value_env(v1, env);
	char pwd[4096]; // PATH_max 4096
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		p = ft_strjoin("PWD=", pwd);
		ft_add_value_env(p, env);
		free(p);
	}
	else
	{
		perror("error getcwd()");
		return ;
	}
	ft_add_value_env("SHLVL=1", env);
	// add another value and key 
}
t_envp	*add_env(char **env)
{
	t_envp	*envp;
	int		i;

	if (*env == NULL)
		env_egal_null(&envp);
	else
	{
		i = 0;
		envp = (t_envp*)malloc(sizeof(t_envp));
		if (envp == NULL)
		{
			printf("Error: command found probleme envp\n");
			return (NULL);
		}
		envp->key = to_egal(env[i]);
		envp->value = to_fin(env[i]);
		envp->next = NULL;
		i++;
		while (env[i] != NULL)
		{
			ft_add_value_env(env[i], &envp);
			i++;
		}
	}
	return (envp);
}
void	afficher_env(t_command*cmd, t_envp *env)
{
	t_envp	*tmp;
	int		i;

	tmp = env;
	i = 0;
	if (ft_strcmp(cmd->command_chain[0], "env") == 0) // env with no options or arguments
	{
		while (cmd->command_chain[i])
		{
			if (ft_cmp(cmd->command_chain[i], "env") != 0)
			{
				printf("env: %s: No such file or directory\n", cmd->command_chain[i]);
				return ;
			}
			i++;
		}
	}
	if (ft_strcmp(cmd->command_chain[0], "export") == 0)
	{
		if (cmd->command_chain[1] != NULL)
		{
			export(cmd, &env);
			return ;
		}
	}
	while (tmp != NULL)
	{
		if (tmp->env_path == false)
		{
			if (ft_strcmp(cmd->command_chain[0], "export") == 0 && cmd->command_chain[1] == NULL)
			{
				sort_list(&env);
				check_egal(&env);
				if (tmp->egal_exist == false)
				{
					printf("declare -x %s\"%s\"\n", tmp->key, tmp->value);
				}
				else if (tmp->egal_exist == true)
				{
					printf("declare -x %s%s\n", tmp->key, tmp->value);
				}
			}
			else
			{
				if (tmp->egal_exist == false)
					printf("%s%s\n", tmp->key, tmp->value);
			}
		}
		tmp = tmp->next;
	}
}
