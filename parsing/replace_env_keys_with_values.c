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
				return (i);
		}
		i++;
	}
	return (-1);
}

char *get_value_by_key(char *key, t_envp *list_envp)
{
	char *value;

	value = NULL;
	if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(g_var_globale.g_exit_status);
	else if (ft_isdigit(key[0]))
		value = key + 1;
	else if (key[0] == '\'' || key[0] == '"')
		value = key;
	else
	{
		value = ft_getenv(list_envp, key);
		if (value == NULL)
			value = ft_strdup("");
	}
	return value;
}

size_t calculate_final_str_len(char *str, char *value, int len_key)
{
	return ft_strlen(str) + ft_strlen(value) - len_key;
}

char *allocate_final_str(size_t final_str_len)
{
	char *final_str;

	final_str = (char *)gc_malloc(final_str_len * sizeof(char) + 1);
	if (final_str == NULL)
	{
		gc_remove_ptr(final_str);
		return NULL;
	}
	return final_str;
}

void copy_chars_from_str(char *str, char *final_str, int *i, int *k)
{
	final_str[*k] = str[*i];
	(*i)++;
	(*k)++;
}

void copy_value_to_final_str(char *value, char *final_str, int *k)
{
	int j;

	j = 0;
	while (value[j])
	{
		final_str[*k] = value[j];
		(*k)++;
		j++;
	}
}

void replace_key_with_value(char *str, char *final_str, char *value, int len_key, int target_dollar)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (i != target_dollar)
			copy_chars_from_str(str, final_str, &i, &k);
		else
		{
			if (value[0] != '\0')
				copy_value_to_final_str(value, final_str, &k);
			i += 1 + len_key;
		}
	}
	final_str[k] = '\0';
}

char *replace_env_keys_with_values(char *str, char *key, t_envp *list_envp)
{
	int len_key;
	char *final_str;
	char *value;
	size_t final_str_len;
	int target_dollar;

	len_key = ft_strlen(key);
	value = get_value_by_key(key, list_envp);
	final_str_len = calculate_final_str_len(str, value, len_key);
	final_str = allocate_final_str(final_str_len);
	if (final_str == NULL)
		return NULL;
	target_dollar = get_target_dollar(str, key);
	replace_key_with_value(str, final_str, value, len_key, target_dollar);
	str = final_str;
	return final_str;
}
