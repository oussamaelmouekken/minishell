/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:40:26 by mohamed           #+#    #+#             */
/*   Updated: 2024/09/22 01:06:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_arr(char **cmd_chain)
{
	int	count;

	count = 0;
	while (cmd_chain[count] != NULL)
		count++;
	return (count);
}

char	**create_cmd_chain(char **tmp, int count_words)
{
	char	**new_cmd_chain;
	int		i;

	new_cmd_chain = (char **)gc_malloc(sizeof(char *) * (count_words + 1));
	if (new_cmd_chain == NULL)
		return (NULL);
	i = 0;
	while (i < count_words)
	{
		new_cmd_chain[i] = ft_strdup(tmp[i]);
		i++;
	}
	new_cmd_chain[i] = NULL;
	return (new_cmd_chain);
}

char	**merge_cmd_chain(char **cmd_chain, char **tmp, int count_words)
{
	int		i;
	int		j;
	char	**new_cmd_chain;

	i = 0;
	j = 0;
	while (cmd_chain[i] != NULL)
		i++;
	new_cmd_chain = (char **)gc_malloc(sizeof(char *) * (i + count_words + 1));
	i = 0;
	j = 0;
	while (cmd_chain[i] != NULL)
	{
		new_cmd_chain[i] = ft_strdup(cmd_chain[i]);
		i++;
	}
	while (j < count_words)
	{
		new_cmd_chain[i] = ft_strdup(tmp[j]);
		i++;
		j++;
	}
	new_cmd_chain[i] = NULL;
	return (new_cmd_chain);
}

char	**add_cmd_chain_to_list(char **cmd_chain, char *cmd)
{
	char	**new_cmd_chain;
	char	**tmp;
	int		count_words;

	count_words = 0;
	if (g_var_globale.export_encountered == 1)
	{
		tmp = gc_malloc(sizeof(char *) * 2);
		tmp[0] = ft_strdup(cmd);
		tmp[1] = NULL;
	}
	else
		tmp = ft_split_pro_max(cmd);
	count_words = count_words_arr(tmp);
	if (cmd_chain == NULL)
		new_cmd_chain = create_cmd_chain(tmp, count_words);
	else
		new_cmd_chain = merge_cmd_chain(cmd_chain, tmp, count_words);
	free_double(tmp);
	return (new_cmd_chain);
}
