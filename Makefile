NAME=minishell
CFILE=main.c readline.c errors.c command.c env_commands.c env_extra_funct.c \
		env_funct.c env_tmp_funct.c general_bultins.c extension.c minishell.c
OFILE=$(CFILE:%.c=%.o)
CC= gcc -Iincludes/ -Iincludes/libft/includes -g -Wall -Wextra -Werror
INCL=$(addprefix includes/, mshheader.h)
VPATH= . src/ includes/ includes/libft includes/libft/includes includes/libft/hash_table
LIB=libft.a
LIB_PATH=includes/libft/


all: $(NAME)

$(NAME): $(LIB) $(OFILE)
	$(CC) $(LIB_PATH)$(LIB) $(OFILE) -o $(NAME)
%.o: %.c
	$(CC) -I$(LIB_PATH)$(LIB) -c $< -o $@
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
