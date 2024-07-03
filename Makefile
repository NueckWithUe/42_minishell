NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	src/
SRC		=	main.c

OBJDIR	=	obj/
OBJ		=	$(addprefix $(OBJDIR), $(SRC:%.c=%.o))

LIBFT	=	libft/libft.a

$(NAME):	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

all:		$(NAME)

$(LIBFT):
			cd libft && make

obj/%.o:	$(SRCDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			cd libft && make clean
			rm -rf $(OBJDIR)

fclean:		clean
			cd libft && make fclean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re