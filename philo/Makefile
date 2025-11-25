NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
OBJ		=	$(patsubst %.c, obj/%.o, $(SRC))
SRC		=	main.c philo_utils.c

all:		obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread
			@echo "\033[1;32mPhilo Compiled!\033[0m"

obj:
			@mkdir -p obj

obj/%.o:	%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJ) obj
			@echo "\033[35mObjects deleted.\033[0m"

fclean:	clean
			@rm -rf $(NAME)
			@echo "\033[36mPhilo deleted.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re