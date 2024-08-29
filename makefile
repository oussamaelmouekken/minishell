NAME = minishell
CC = cc 

CEXE = main.c  builtins/exit.c builtins/cd.c builtins/pwd.c builtins/env.c builtins/echo_n.c builtins/unset.c builtins/export.c execution/execute.c execution/utils_ex.c execution/herdoc.c
CPARS = parsing/parser_phase.c parsing/ft_split_pro_max.c parsing/expansion_phase.c parsing/lexer_phase.c parsing/remove_quotes.c parsing/replace_env_keys_with_values.c parsing/syntax_error.c parsing/utils.c parsing/libft1.c
CLIBFT = libft/ft_split.c libft/ft_substr.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_putstr_fd.c libft/ft_isalnum.c libft/ft_isalpha.c
OBJ = ${CEXE:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(CLIBFT) $(CPARS) $(OBJ) $(FLAGS) -lreadline -o  $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re