NAME = minishell
CC = cc 
CUTILS = builtins/utils_export_env/utils_export.c builtins/utils_export_env/export1.c  builtins/utils_export_env/export2.c builtins/utils_export_env/export3.c  builtins/utils_export_env/utils_env.c
CEXE =  execution/garbage_collector.c execution/var_use.c execution/execute2.c execution/execute1.c execution/free.c execution/signal.c main.c  builtins/exit.c builtins/cd.c builtins/pwd.c builtins/env.c builtins/echo_n.c builtins/unset.c builtins/export.c execution/execute.c execution/utils_ex.c execution/herdoc.c
CPARS =parsing/parser_utils.c parsing/lexer_utils1.c parsing/add_spaces_around.c parsing/utils2.c parsing/expansion_utils.c parsing/ft_split_pro_max_utils.c parsing/syntax_error2.c  parsing/parser_phase.c parsing/ft_split_pro_max.c parsing/expansion_phase.c parsing/lexer_phase.c parsing/remove_quotes.c  parsing/syntax_error.c parsing/utils.c parsing/libft1.c
CLIBFT = libft/ft_cmp.c libft/ft_itoa.c libft/ft_atoi.c libft/ft_split.c libft/ft_substr.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_strjoin.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strdup.c  libft/ft_isalnum.c libft/ft_isalpha.c
OBJ = ${CEXE:.c=.o}
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(CLIBFT) $(CPARS) $(CUTILS) $(OBJ) $(FLAGS) -lreadline -o  $(NAME)
	@echo "successfully! ✅✅✅"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Object files cleaned! 🧹🧹🧹"

fclean: clean
	@rm -f $(NAME)
	@echo "cleaned all!"

re: fclean all

.PHONY : all clean fclean re
