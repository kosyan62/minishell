NAME=minishell
CFILE=main.c readline.c error.c command.c env_commands.c env_extra_funct.c \
		env_funct.c env_tmp_funct.c general_bultins.c extension.c minishell.c
OFILE=$(CFILE:%.c=%.o)
CC= gcc -Iincludes -Iincludes/libft/includes -Iincludes/ -Wall -Wextra -Werror
INCL=$(addprefix includes/, mshheader.h)
VPATH= . src/ includes/ includes/libft includes/libft/includes includes/libft/hash_table
LIB=ft
LIB_PATH=includes/libft/


all: $(NAME)

$(NAME): $(LIB) $(OFILE)
	$(CC) $(OFILE) -L$(LIB_PATH) -l$(LIB) -o $(NAME)
%.o: %.c
	$(CC) -c $< -L$(LIB_PATH) -l$(LIB) -o $@ 
$(LIB):
	$(MAKE) -C $(LIB_PATH)
clean:
	rm -f $(OFILE)
	@make -C $(LIB_PATH) clean
fclean: clean
	rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
norm: $(NAME)
	norminette */**.c */**.h
re: fclean all
