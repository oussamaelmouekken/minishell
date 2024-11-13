/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:59:55 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/17 19:15:33 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int					ft_atoi(char *str);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int n);
int					ft_isdigit(int n);
int					ft_isprint(int c);
char				*ft_itoa(int n);

char				**ft_split(char *s, char c);
char				*ft_strchr(char *str, int c);
char				*ft_strdup(char *src);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlcat(char *dest, char *src, int dstsize);
int					ft_strlcpy(char *dest, char *src, int dstsize);
int					ft_strlen(char *str);

int					ft_strncmp(char *s1, char *s2, size_t n);
char				*ft_strnstr(const char *str, const char *rechr, size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_substr(char *s, int start, int len);
int					ft_cmp(char *s1, char *s2);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *new);
int					ft_strcmp(char *s1, char *s2);

#endif // LIBFT_H
