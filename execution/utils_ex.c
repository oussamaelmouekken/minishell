/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:42:24 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 13:45:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_of_list(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**add_env_arr(t_envp *env)
{
	t_envp	*tmp;
	int		i;
	char	**str;

	tmp = env;
	i = 0;
	g_var_globale.size_list = size_of_list(env);
	str = gc_malloc(sizeof(char *) * (g_var_globale.size_list + 1));
	if (!str)
	{
		printf("Memory allocation failed\n");
		return (NULL);
	}
	while (tmp)
	{
		str[i] = ft_strjoin(tmp->key, tmp->value);
		if (str[i] == NULL)
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

void	change_shlvl(t_envp **envp)
{
	char	*v;
	int		nbr_shlvl;
	t_envp	*tmp;

	tmp = *envp;
	while (envp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			nbr_shlvl = ft_atoi(tmp->value) + 1;
			if (nbr_shlvl >= 100)
			{
				write(2, "warning: shell level (1000) too high\n", 37);
				nbr_shlvl = 1;
				g_var_globale.g_exit_status = 1;
			}
			gc_remove_ptr(tmp->value);
			v = ft_itoa(nbr_shlvl);
			tmp->value = ft_strdup(v);
			gc_remove_ptr(v);
			return ;
		}
		tmp = tmp->next;
	}
}

void	restore_in_out(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

int	write_ambiguous1(t_file *file)
{
	if (file->is_ambiguous == true && file->file_type != REDIRECT_IN)
	{
		write_ambiguous(file);
		return (-1);
	}
	return (0);
}
