NAME = minishell

CC = cc

 CFLAGS = -Wall -Wextra -Werror 

LDFLAGS = -lreadline

RM = rm -rf 

SRC = error.c expand.c free.c filling_list.c filling_command.c filling_redirections.c help_join.c help.c join.c main.c split_cmd_by_quote.c split_cmd_by_space.c 
 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) minishell.h
	make -C libft
	$(CC)  $(OBJ) libft/libft.a $(LDFLAGS) -o $(NAME)

clean:
	make -C libft clean
	$(RM) $(OBJ) 

fclean: clean
	make -C libft fclean
	$(RM) $(NAME) 

re: fclean all