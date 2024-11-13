/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:05:03 by oel-moue          #+#    #+#             */
/*   Updated: 2024/09/22 13:03:23 by oel-moue         ###   ########.fr       */
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

# define G_TTY "\033[1;32m"
# define RESET "\033[0m"

enum					e_token_type
{
	PIPE,
	REDIRECT_OUT,
	REDIRECT_IN,
	REDIRECT_APPEND,
	REDIRECT_INPUT,
	WORD,
};

typedef struct expansion_vars
{
	int					i;
	int					inside_single_quotes;
	int					inside_double_quotes;
	char				*final_str;
}						t_expansion_vars;

typedef struct parser_state
{
	char				*modified_input;
	int					i;
	int					j;
	int					inside_double_quotes;
	int					inside_single_quotes;
}						t_parser_state;

typedef struct args_for_remove_quotes
{
	char				**str;
	char				*new_str;
	int					*i;
	int					*j;
	char				current_quote;
}						t_args_for_remove_quotes;

typedef struct s_gc_node
{
	void				*ptr;
	int					is_freed;
	struct s_gc_node	*next;
}						t_gc_node;
typedef struct t_us
{
	int					signal_exit;
	int					fd_in;
	int					fd_out;
	int					fd_herdoc;
	int					nb_cmd;
	int					nbr_herdoc;
	int					*pid;
	int					**fd;
	int					k;
}						t_us;

typedef struct lexer_state
{
	int					inside_quotes;
	int					current_word_len;
	int					start;
	int					i;
	char				*current_word;
	enum e_token_type	type;
}						t_lexer_state;
typedef struct lexer
{
	char				*value;
	enum e_token_type	type;
	struct lexer		*prev;
	struct lexer		*next;
}						t_lexer;
typedef struct envp
{
	char				*key;
	char				caracter_egal;
	char				*value;
	bool				env_path;
	bool				egal_exist;
	struct envp			*next;
}						t_envp;

typedef struct t_file
{
	char				*file_name;
	enum e_token_type	file_type;
	bool				is_quoted;
	bool				is_ambiguous;
	struct t_file		*next;
}						t_file;

typedef struct command
{
	char				**command_chain;
	t_file				*file;
	struct command		*next;
}						t_command;

typedef struct for_free
{
	int					g_exit_status;
	int					size_list;
	int					export_encountered;
	char				**env_arr;
	t_command			*cmd;
	t_envp				*envp;
	t_us				*var;
	t_gc_node			*gc;
	struct for_free		*next;
}						t_global;

extern t_global			g_var_globale;

// execution part
void					write_int(t_us *var);
void					write_quit(t_us *var);
int						write_ambiguous1(t_file *file);
void					restore_in_out(int in, int out);
void					gc_remove_ptr(void *ptr);
void					*gc_malloc(size_t size);
void					gc_free_all(void);
int						size_of_list(t_envp *env);
char					*check_to_egal(char *first);
char					*delet_plus(char *str);
void					join_node(char *str, char *data_fin, t_envp **env);
int						check_exist_node_with_ncmp(char *str, t_envp *env);
int						check_exist_node_with_cmp(char *str, t_envp *env);
int						check_plus(char *str);
void					check_egal_and_addegal(char *str, t_envp **env);
void					change_data(char *str, char *fin, t_envp **env);
int						if_egal(char *str);
int						ft_strlen_to_char(char *str, char c);
void					free_2(char *first, char *fin);
void					exe_builtins(t_command *cmd, t_envp **envp);
void					exe(t_command *cmd, t_envp **envp, char **env);
int						is_builtins(t_command *cmd);
void					single_cmd_builting(t_us *var, t_command *cmd,
							t_envp *envp);
char					*true_path(char *cmd, char **env);
void					change_shlvl(t_envp **envp);
int						outfile(t_command *cmd);
int						infile(t_command *cmd, t_us *var);
void					perent(t_command *cmd, t_us *var);
void					write_ambiguous(t_file *file);
int						var_and_single_built(t_command *cmd, t_us *var,
							t_envp *envp);
int						nbr_cmd(t_command *cmd);
int						erro_malloc(t_envp *n);
void					init_(t_envp *new_node);

void					free_double(char **str);
void					free_command_list(t_command *cmd);

void					handl_sigint_herdoc(int sig);
void					hanld_siquit(int sig);
void					handl_sigint(int sig);
void					my_exit(t_command *cmd);
int						herdoc(t_command *cmd, t_us *var, t_envp *env);
int						count_herdoc(t_command *cmd);
void					close_all(t_us *var);
void					join(char *n, t_envp *env, char *fin);
void					add_v(char *n, char *fin, t_envp *env);
int						handle_check_plus(char *str, t_envp *env, char *first,
							char *fin);
int						fct2(char *str, t_envp *env, char *fin);

int						check_exist_node(char *new_first, t_envp *env,
							char *first, char *fin);
int						fct3(char *first, char *fin, char *new_first,
							t_envp *env);
char					**add_env_arr(t_envp *env);
void					pwd(void);
void					cd(t_command *cmd, t_envp *env);
void					write_and_free(char *input);
t_envp					*add_env(char **env);
void					afficher_env(t_command *cmd, t_envp *env);
void					echo_n(t_command *cmd);
char					*ft_setenv(char *variable, t_envp *env);
void					unset(t_command *cmd, t_envp **env);
void					ft_add_value_env(char *node, t_envp **env);
void					export(t_command *cmd, t_envp **env);
char					*to_fin(char *str);
char					*to_egal(char *str);
int						check_if_egal_exit(char *str);
void					sort_list(t_envp **env);
void					check_egal(t_envp **env);
void					execute_command(t_command *cmd, t_envp *t_envp,
							char **env);
void					execute_cmd(t_command *cmd, char **env);
// void					show_command(t_command *command);
char					*ft_getenv(char *key);

// expansion functions
char					*append_char_to_string(char *str, char c);
char					*append_alnum(char *key, char *value, int *i);
char					*replace_env_keys_with_values(char *str, char *key,
							t_envp *list_envp);
int						get_target_dollar(char *str, char *key);
void					remove_quotes(char **str);
void					expansion_phase(t_lexer **lexer);
char					*expansion(char *str);
char					*get_value_by_key(char *key);
size_t					calculate_final_str_len(char *str, char *value,
							int len_key);
char					*allocate_final_str(size_t final_str_len);
void					copy_chars_from_str(char *str, char *final_str, int *i,
							int *k);
void					copy_value_to_final_str(char *value, char *final_str,
							int *k);
char					*handle_digit(char *str, int *i, char *final_str);
char					*handle_alnum(char *str, int *i, char *final_str);
char					*handle_special_char(int *i, char *final_str,
							char special_char);
char					*handle_quote(char *str, int *i, char *final_str);
void					process_key(char *str, t_expansion_vars *phase);
void					handle_quotes(char c, int *inside_single_quotes,
							int *inside_double_quotes);
char					*get_from_quotes(char *key, char *str, int *i);
// string manipulation functions
int						is_alnum_or_underscore(char c);
size_t					strlen_to_char(const char *s, char c);
char					*add_spaces_around_special_chars(const char *input);
int						check_for_closed_quotes(char *input);
char					**ft_split_pro_max(char *s);
int						count_words(char *s);
void					process_command_chain_and_files(t_command *command);
void					toggle_quotes(char c, bool *in_quotes,
							char *quote_char);
int						count_words(char *s);
char					*ft_remove_equal(char *str);
int						is_equal(char *s1, char *s2);

// lexer functions
void					lexer_phase(t_lexer **lexer, char *input);
t_lexer					*create_lexer_node(char *value, enum e_token_type type);
void					append_lexer_node(t_lexer **lexer, t_lexer *new_node);
void					show_lexer(t_lexer *lexer);
t_lexer					*get_last_node(t_lexer *head);
void					init_lexer_phase(t_lexer_state *phase);
void					process_current_word(t_lexer_state *state, char *input,
							void *lexer);
void					process_redirect(t_lexer_state *state, char *input);
void					process_redirect1(t_lexer_state *state, char *input);
void					process_pipe(t_lexer_state *state, char *input);

// parser functions
t_command				*parser_phase(t_lexer *lexer);
t_command				*add_command_to_list(t_command **list_of_commands,
							char **cmd_chain, t_file **file);
t_file					*add_file_to_list(t_file **file, char *file_name,
							enum e_token_type file_type);
char					**add_cmd_chain_to_list(char **cmd_chain, char *value);
int						count_words_arr(char **cmd_chain);
char					**create_cmd_chain(char **tmp, int count_words);
char					**merge_cmd_chain(char **cmd_chain, char **tmp,
							int count_words);

// general functions
void					minishell_process(t_lexer **lexer, t_envp *list_envp);
int						syntax_error(t_lexer *lexer);
void					free_lexer_list(t_lexer **lexer);
int						print_error(t_lexer **lexer, char *str, char *str1);
int						is_lexer_null(t_lexer **lexer);
int						is_initial_pipe(t_lexer **lexer);

#endif