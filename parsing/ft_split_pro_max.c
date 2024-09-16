
#include "../minishell.h"

int count_words(char *s)
{
    int count = 0;
    int i = 0;
    bool in_quotes = false;

    while (s && s[i] != '\0')
    {
        while ((s[i] == ' ' || s[i] == '\t') && !in_quotes)
            i++;
        if (s[i] == '\0')
            break;
        count++;
        while (s[i] != '\0' && (in_quotes || (s[i] != ' ' && s[i] != '\t')))
        {
            if (s[i] == '"')
                in_quotes = !in_quotes;
            i++;
        }
    }
    return count;
}

static char **free_list(char **str, int n)
{
    while (n >= 0)
    {
        free(str[n]);
        n--;
    }
    free(str);
    return (NULL);
}

char **allocate_memory(char *s)
{
    char **ptr = (char **)malloc((count_words(s) + 1) * sizeof(char *));
    if (ptr == NULL)
        return NULL;
    return ptr;
}

char *parse_word(char *s, int *i, bool *in_quotes)
{
    int j = 0;
    int start = *i;
    while (s[*i] != '\0' && (*in_quotes || (s[*i] != ' ' && s[*i] != '\t')))
    {
        if (s[*i] == '"')
            *in_quotes = !(*in_quotes);
        (*i)++;
        j++;
    }
    return ft_substr(s, start, j);
}

char **ft_split_pro_max(char *s)
{
    char **ptr;
    int i;
    int n;
    bool in_quotes;

    i = 0;
    n = 0;
    in_quotes = false;
    ptr = allocate_memory(s);
    if (ptr == NULL)
        return NULL;
    while (s && s[i] != '\0')
    {
        while ((s[i] == ' ' || s[i] == '\t') && !in_quotes)
            i++;
        if (s[i] == '\0')
            break;
        ptr[n] = parse_word(s, &i, &in_quotes);
        if (ptr[n] == NULL)
            return free_list(ptr, n);
        n++;
    }
    ptr[n] = NULL;
    return ptr;
}
