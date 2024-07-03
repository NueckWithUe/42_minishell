NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	src/
SRC		=	main.c

PARSDIR	=	src/parser/
PARSSRC	=	parser.c

OBJDIR	=	obj/
OBJ		=	$(addprefix $(OBJDIR), $(SRC:%.c=%.o))
PARSOBJ	=	$(addprefix $(OBJDIR), $(PARSSRC:%.c=%.o))

LIBFT	=	libft/libft.a

$(NAME):	$(LIBFT) $(OBJ) $(PARSOBJ)
			$(CC) $(CFLAGS) $(LIBFT) $(OBJ) $(PARSOBJ) -o $(NAME)

all:		$(NAME)

$(LIBFT):
			cd libft && make

obj/%.o:	$(SRCDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(PARSDIR)%.c
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