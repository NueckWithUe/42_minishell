NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address

SRCDIR	=	src/
SRC		=	main.c

PARSDIR =	src/parsing/
PARSSRC =	token.c \
			token_of_chars.c \
			command_ast.c \
			lexer_tokenizer.c \
			parsing.c


UTILDIR	=	src/parsing/utils/
UTILSRC	=	util.c \
			util_cmd.c \
			utils_expand.c \
			utils_expand1.c \
			util_herdoc.c

REDIDIR	=	src/parsing/redirects/
REDISRC	=	redire_pipe_syntax.c \
			redirection_handler.c \
			redirects_herdoc.c


FREEDIR	=	src/parsing/free/
FREESRC	=	free_token.c \
			free.c

EXPDIR	=	src/parsing/expand/
EXPSRC	=	expand_quote.c \
			expands.c \
			expand_env.c

FREDIR	=	src/free_exc/
FRESRC	=	free_exc.c

EXCDIR	=	src/execution/
EXCSRC	=	simple_exc.c \
			error_handl.c \
			find_path.c \
			fd.c \
			fd1.c \
			excusion.c \
			part.c \
			utils.c \
			process1.c \
			process.c \
			exit.c \
			mult_exc.c


SIGDIR	=	src/signal/
SIGSRC	=	signal.c

TERDIR	=	src/terminal/
TERSRC	=	terminal.c \
			utils_terminal.c \
			utils_terminal1.c \
			utils_terminal2.c \
			utils_terminal3.c \
			terminal_path.c \
			init_envp.c \
			host.c

CDDIR	=	src/builtins/cd/
CDSRC	=	cd.c

ECHODIR	=	src/builtins/echo/
ECHOSRC	=	echo.c

ENVDIR	=	src/builtins/env/
ENVSRC	=	env.c

USETDIR	=	src/builtins/unset/
USETSRC	=	unset.c

EXPODIR	=	src/builtins/export/
EXPOSRC	=	export.c \
			add_exports.c \
			export_utils.c

UTILSDIR	=	src/utils/
UTILSSRC	=	utilities.c

OBJDIR	=	obj/
SRCOBJ	=	$(addprefix $(OBJDIR), $(SRC:.c=.o))
PARSOBJ	=	$(addprefix $(OBJDIR), $(PARSSRC:.c=.o))
UTILOBJ	=	$(addprefix $(OBJDIR), $(UTILSRC:.c=.o))
REDIOBJ	=	$(addprefix $(OBJDIR), $(REDISRC:.c=.o))
FREEOBJ	=	$(addprefix $(OBJDIR), $(FREESRC:.c=.o))
EXPOBJ	=	$(addprefix $(OBJDIR), $(EXPSRC:.c=.o))
SIGOBJ	=	$(addprefix $(OBJDIR), $(SIGSRC:.c=.o))
PIPOBJ	=	$(addprefix $(OBJDIR), $(PIPSRC:.c=.o))
TEROBJ	=	$(addprefix $(OBJDIR), $(TERSRC:.c=.o))
EXCOBJ	=	$(addprefix $(OBJDIR), $(EXCSRC:.c=.o))
FREOBJ	=	$(addprefix $(OBJDIR), $(FRESRC:.c=.o))
OBJS	=	$(SRCOBJ) $(PARSOBJ) $(UTILOBJ) $(REDIOBJ) $(FREEOBJ) $(EXPOBJ) $(SIGOBJ) $(TEROBJ) $(PIPOBJ)
CDOBJ	=	$(addprefix $(OBJDIR), $(CDSRC:.c=.o))
ECHOOBJ	=	$(addprefix $(OBJDIR), $(ECHOSRC:.c=.o))
ENVOBJ	=	$(addprefix $(OBJDIR), $(ENVSRC:.c=.o))
USETOBJ	=	$(addprefix $(OBJDIR), $(USETSRC:.c=.o))
EXPOOBJ	=	$(addprefix $(OBJDIR), $(EXPOSRC:.c=.o))
UTILSOBJ	=	$(addprefix $(OBJDIR), $(UTILSSRC:.c=.o))
OBJS	=	$(SRCOBJ) $(PARSOBJ) $(UTILOBJ) $(REDIOBJ) $(FREEOBJ) $(EXPOBJ) $(SIGOBJ) $(PIPOBJ) $(CDOBJ) $(TEROBJ) $(FREOBJ) $(EXCOBJ) $(UTILSOBJ)

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) -lreadline

$(LIBFT):
	cd libft && make

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(PARSDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(UTILDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(REDIDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(FREEDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(EXPDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(SIGDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(TERDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(PIPDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(FREDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(EXCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(CDDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(ECHODIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(ENVDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(USETDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(UTILSDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(EXPODIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd libft && make clean
	rm -rf $(OBJDIR)

fclean: clean
	cd libft && make fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
