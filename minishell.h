/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:05:03 by oel-moue          #+#    #+#             */
/*   Updated: 2024/08/19 22:29:11 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
enum				token_type
{
	PIPE,            // = |
	REDIRECT_OUT,    // = >
	REDIRECT_IN,     // = <
	REDIRECT_APPEND, // = >>
	REDIRECT_INPUT,  //= <<
	WORD,
};
typedef struct lexer
{
	char			*value;
	enum token_type	type;
	struct lexer	*prev;
	struct lexer	*next;
}					t_lexer;
typedef struct envp
{
	char			*key;
	char			*value;
	bool			env_path;
	bool			egal_exist;
	struct envp		*next;
}					t_envp;

typedef struct t_file
{
	char			*file_name;
	enum token_type	file_type;
	struct t_file	*next;
}					t_file;

typedef struct command
{
	char			**command_chain;
	t_file			*file;
	struct command	*next;
}					t_command;
// execution part
// void				exe(char *line, char **av, t_envp **env);
void				print_minishell(void);
char				**add_env_arr(t_envp *env);
void				pwd(void);
void				cd(t_command *cmd, t_envp *env);
t_envp				*add_env(char **env);
void				afficher_env(t_command *cmd, t_envp *env);
void				echo_n(t_command *cmd);
char				*ft_getenv(char *variable, t_envp *env);
void				unset(t_command *cmd, t_envp **env);
void				ft_add_value_env(char *node, t_envp **env);
void				export(t_command *cmd, t_envp **env);
char				*to_fin(char *str);
char				*to_egal(char *str);
int					check_if_egal_exit(char *str);
int					ft_cmp(char *s1, char *s2);
void				sort_list(t_envp **env);
void				check_egal(t_envp **env);
void				execute_command(t_command *cmd, t_envp *t_envp, char **env);
void				execute_cmd(t_command *cmd, char **env);
void				show_command(t_command *command);
// expansion functions
char				*expansion(char *value, t_envp *list_envp);
char				*append_char_to_string(char *str, char c);
char				*append_alnum(char *key, char *value, int *i);
char				*replace_env_keys_with_values(char *str, char *key,
						t_envp *list_envp);
int					get_target_dollar(char *str, char *key);
void				remove_quotes(char **str);

// string manipulation functions
int					is_alnum_or_underscore(char c);

int					ft_strcmp_p(const char *s1, const char *s2);

size_t				strlen_to_char(const char *s, char c);
char				*add_spaces_around_special_chars(const char *input);
int					check_for_closed_quotes(char *input);

// environment functions
t_envp				*create_environment_node(char **envp);
t_envp				*create_environment_node(char **envp);
t_envp				*create_envp_node(char *value);
void				append_envp_node(t_envp **envir, t_envp *new_node);

// lexer functions
void				lexer_phase(t_lexer **lexer, char *input,
						t_envp *list_envp);
t_lexer				*create_lexer_node(char *value, enum token_type type);
void				append_lexer_node(t_lexer **lexer, t_lexer *new_node);
void				show_lexer(t_lexer *lexer);
t_lexer				*get_last_node(t_lexer *head);

// parser functions
t_command			*parser_phase(t_lexer *lexer);
void				free_commands(t_command *command);

// general functions
void				minishell_process(t_lexer **lexer, t_envp *list_envp);
int					syntax_error(t_lexer *lexer);
void				free_list(t_lexer **lexer);

#endif