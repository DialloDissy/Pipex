
NAME = pipex
BONUS_NAME = pipex_bonus

FLAG = -g -Wall -Wextra -Werror
CC = cc 

SRC = mandatory/pipex.c\
      mandatory/process_execve.c\
	  mandatory/process_pip.c\

SRC_BONUS = bonus/pipex_bonus.c\
			bonus/process_execve_bonus.c\
			bonus/process_pip_bonus.c\
			bonus/here_doc_bonus.c\




OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	mv libft/libft.a .
	$(CC) $(OBJ) -g -L. -lft -o $(NAME)  
	
bonus: $(BONUS_NAME)

$(BONUS_NAME) : $(OBJ_BONUS)
	make -C libft
	mv libft/libft.a .
	$(CC) $(OBJ_BONUS) -g -L. -lft -o $(BONUS_NAME)  

%.o : %.c
	$(CC) $(FLAG) -o $@ -c $<

clean:
	make -C libft clean
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME) libft.a $(BONUS_NAME)

re : fclean all

.PHONY : all clean fclean re bonus
