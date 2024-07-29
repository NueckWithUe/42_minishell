NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	src/
SRC		=	main.c

PARSDIR	=	src/parser/
PARSSRC	=	parser.c

LEXDIR	=	src/lexer/
LEXSRC	=	lexer.c \
			lexer_utils.c

PIPDIR	=	src/pipes/
PIPSRC	=	pipes.c \
			pipe_utils.c

UTILDIR	=	src/utils/
UTILSRC	=	utils.c

CDDIR	=	src/builtins/cd/
CDSRC	=	cd.c

ECHODIR	=	src/builtins/echo/
ECHOSRC	=	echo.c

ENVDIR	=	src/builtins/env/
ENVSRC	=	env.c

USETDIR	=	src/builtins/unset/
USETSRC	=	unset.c

EXPDIR	=	src/builtins/export/
EXPSRC	=	export.c

OBJDIR	=	obj/
OBJS	=	$(addprefix $(OBJDIR), $(SRC:%.c=%.o) $(PARSSRC:%.c=%.o) $(LEXSRC:%.c=%.o) $(PIPSRC:%.c=%.o) $(UTILSRC:%.c=%.o) $(CDSRC:%.c=%.o) $(ECHOSRC:%.c=%.o) $(ENVSRC:%.c=%.o) $(USETSRC:%.c=%.o) $(EXPSRC:%.c=%.o))

LIBFT	=	libft/libft.a

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

all:		$(NAME)

$(LIBFT):
			cd libft && make

obj/%.o:	$(SRCDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(PARSDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(LEXDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(PIPDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(UTILDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(CDDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(ECHODIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(ENVDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(USETDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(EXPDIR)%.c
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