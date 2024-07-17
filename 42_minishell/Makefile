NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCDIR	=	src/
SRC		=	main.c

PARSDIR =	src/parsing/
PARSSRC =	token.c \
			token_of_chars.c \
			command_ast.c \
			lexer_tokenizer.c

UTILDIR	=	src/parsing/utils/
UTILSRC	=	util.c \
			util_cmd.c \
			utils_expand.c \
			utils_expand1.c

REDIDIR	=	src/parsing/redirects/
REDISRC	=	redire_pipe_syntax.c \
			redirection_handler.c \
			redirects.c

FREEDIR	=	src/parsing/free/
FREESRC	=	free_token.c

EXPDIR	=	src/parsing/expand/
EXPSRC	=	expand_quote.c \
			expands.c

SIGDIR	=	src/signal/
SIGSRC	=	signal.c

PIPDIR	=	src/pipes/
PIPSRC	=	pipes.c

OBJDIR	=	obj/
# OBJ		=	$(addprefix $(OBJDIR), $(SRC:%.c=%.o))
# REDIOBJ	=	$(addprefix $(OBJDIR), $(REDISRC:%.c=%.o))
# PARSOBJ	=	$(addprefix $(OBJDIR), $(PARSSRC:%.c=%.o))
# UTILOBJ	=	$(addprefix $(OBJDIR), $(UTILSRC:%.c=%.o))
# FREEOBJ	=	$(addprefix $(OBJDIR), $(FREESRC:%.c=%.o))
# EXPOBJ	=	$(addprefix $(OBJDIR), $(EXPSRC:%.c=%.o))
# SIGOBJ	=	$(addprefix $(OBJDIR), $(SIGSRC:%.c=%.o))

OBJS	=	$(addprefix $(OBJDIR), $(SRC:%.c=%.o) $(PARSSRC:%.c=%.o) $(UTILSRC:%.c=%.o) $(REDISRC:%.c=%.o) $(FREESRC:%.c=%.o) $(EXPSRC:%.c=%.o) $(SIGSRC:%.c=%.o) $(PIPSRC:%.c=%.o))

LIBFT	=	libft/libft.a

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) -lreadline

all:		$(NAME)

$(LIBFT):
			cd libft && make

obj/%.o:	$(SRCDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(PARSDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(UTILDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(REDIDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(FREEDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(EXPDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(SIGDIR)%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

obj/%.o:	$(PIPDIR)%.c
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