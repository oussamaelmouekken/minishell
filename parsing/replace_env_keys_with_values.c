/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_keys_with_values.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:04:42 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/16 10:36:47 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int get_target_dollar(char *str, char *key)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            j = i + 1;
            while (str[j] == key[k] && key[k] != '\0')
            {
                j++;
                k++;
            }
            if (k == ft_strlen(key))
                return i;
        }
        i++;
    }
    return -1;
}

char *replace_env_keys_with_values(char *str, char *key, t_envp *list_envp)
{
    if(list_envp == NULL) // mast3mltich had lvariable
     return NULL;
    char *value;
    int i;
    int k;
    int j;
    size_t final_str_len;
    char *final_str;
    int len_key;
    int target_dollar;

    len_key = ft_strlen(key);
    value = getenv(key);//env with struct
    if (ft_strcmp_p(key, "?") == 0)
        value = ft_strdup("0");
    else if(ft_isdigit(key[0]))
        value = key + 1;
    else if (value == NULL)
        value = ft_strdup("");
    

    final_str_len = ft_strlen(str) + ft_strlen(value) - len_key + 1;
    final_str = (char *)malloc(final_str_len * sizeof(char));
    if (final_str == NULL)
    {
        free(final_str);
        return NULL;
    }

    i = 0;
    k = 0;
    target_dollar = get_target_dollar(str, key);
    while (str[i])
    {
        if (i != target_dollar)
        {
            final_str[k] = str[i];
            i++;
            k++;
        }
        else
        {
            j = 0;
            if (value[0] != '\0')
                while (value[j])
                {
                    final_str[k] = value[j];
                    k++;
                    j++;
                }
            i += 1 + len_key;
        }
    }

    final_str[k] = '\0';
    str = final_str;
    return final_str;
}
