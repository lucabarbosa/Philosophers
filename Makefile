NAME		=	philo
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))
SRC		=	main.c \
			

all:		$(LIBFT) obj $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $@ $^
			@echo "\033[32mPhilo Compiled!\033[0m"

obj:
			@mkdir -p obj

obj/%.o:	%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
			@rm -rf $(OBJ) obj
			@echo "\033[1;35mObjects deleted.\033[0m"

fclean:	clean
			@make -s fclean
			@rm -rf $(NAME)
			@echo "\033[1;36mPhilo deleted.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
