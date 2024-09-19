
#include "../minishell.h"

int	count_words(char *s)
{
	int		count;
	int		i;
	bool	in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = false;
	quote_char = '\0';
	while (s && s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && !in_quotes)
			i++;
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] != '\0' && (in_quotes || (s[i] != ' ' && s[i] != '\t')))
		{
			if ((s[i] == '"' || s[i] == '\''))
			{
				if (!in_quotes)
				{
					in_quotes = true;
					quote_char = s[i];
				}
				else if (s[i] == quote_char)
				{
					in_quotes = false;
					quote_char = '\0';
				}
			}
			i++;
		}
	}
	return (count);
}

static char	**free_list(char **str, int n)
{
	while (n >= 0)
	{
		gc_remove_ptr(str[n]);
		n--;
	}
	gc_remove_ptr(str);
	return (NULL);
}

char	**allocate_memory(char *s)
{
	char	**ptr;

	ptr = (char **)gc_malloc((count_words(s) + 1) * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

char	*parse_word(char *s, int *i, bool *in_quotes, char *quote_char)
{
	int	j;
	int	start;

	j = 0;
	start = *i;
	while (s[*i] != '\0' && (*in_quotes || (s[*i] != ' ' && s[*i] != '\t')))
	{
		if ((s[*i] == '"' || s[*i] == '\''))
		{
			if (!*in_quotes)
			{
				*in_quotes = true;
				*quote_char = s[*i];
			}
			else if (s[*i] == *quote_char)
			{
				*in_quotes = false;
				*quote_char = '\0';
			}
		}
		(*i)++;
		j++;
	}
	return (ft_substr(s, start, j));
}

char	**ft_split_pro_max(char *s)
{
	char	**ptr;
	int		i;
	int		n;
	bool	in_quotes;
	char	quote_char;

	i = 0;
	n = 0;
	in_quotes = false;
	quote_char = '\0';
	ptr = allocate_memory(s);
	if (ptr == NULL)
		return (NULL);
	while (s && s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && !in_quotes)
			i++;
		if (s[i] == '\0')
			break ;
		ptr[n] = parse_word(s, &i, &in_quotes, &quote_char);
		if (ptr[n] == NULL)
			return (free_list(ptr, n));
		n++;
	}
	ptr[n] = NULL;
	return (ptr);
}
