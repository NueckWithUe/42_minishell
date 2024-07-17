/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/17 09:23:39 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "libft.h"
# define DEBUG 0

//blatifat
typedef enum s_type
{
	WORD,
	PIPE,
	APP_OUT,
	HEAD_DOC,
	EOL,
	ERROR
}	t_type;

typedef struct s_token_struct
{
	t_type					type;
	char					*value;
	struct s_token_struct	*next;
	struct s_token_struct	*prev;
}	t_token_struct;

typedef struct s_lexer_struct
{
	char	*line;
	int		position;
	int		dbl_quote;
	int		spl_quote;
}	t_lexer_struct;

typedef struct s_asset
{
	struct s_asset	*next;
	struct s_asset	*prev;
	char			**args;
	int				fd_infile;
	int				fd_outfile;
}	t_asset;

typedef struct s_minishell
{
	char			*name_of_term;
	char			**fds;
	char			*readline;
	char			*pwd;
	char			*home;
	char			**envp;
	int				*pids;
	int				cd_quite;
	int				fd_input;
	int				fd_output;
	t_lexer_struct	lexer_data;
	t_token_struct	*token;
	t_asset			*commands;
	pid_t			*pid;
}	t_minishell_struct;

typedef struct s_env_var_data
{
	char	*env_var;
	char	*env_value;
}	t_env_var_data;


t_token_struct	*initialize_token(t_type type, char *value,
		t_token_struct *next, t_token_struct *prev);
t_token_struct	*handle_special_chars(t_lexer_struct *lexer,
		char current_char, char next_char);
t_token_struct	*next_token(t_lexer_struct *lexer);
void			parse_quote(t_lexer_struct *lexer_data);
void			handle_quotes(t_lexer_struct *lexer);
int				check_if_space(int c);
t_token_struct	*extract_token_word(t_lexer_struct *lexer);
t_token_struct *handle_less_than(t_lexer_struct *lexer, char next_char);
t_token_struct *handle_greater_than(t_lexer_struct *lexer, char next_char);
// lexical
void	print_token(t_token_struct *token, const char *msg);
void	print_list_of_token(t_token_struct *list, const char *msg);
int	tokenize_line(t_lexer_struct *lexer_data, t_minishell_struct *mini_data);
int	is_lexically_valid(t_minishell_struct *mini_data);
void	free_if_not_null(char *str);
void	free_list_of_token(t_token_struct *token);
int	is_lexically_valid(t_minishell_struct *mini_data);
int	tokenize_line(t_lexer_struct *lexer_data, t_minishell_struct *mini_data);
void	print_token(t_token_struct *token, const char *msg);
int	validate_syntax(t_minishell_struct *mini_data);
int	pipe_sytx_error(t_token_struct *token);
int	redirection_sytx_error(t_token_struct *token);
int	generat_ast_cmd_instruct(t_minishell_struct *mini_data);
int	insert_new_ast_node(t_token_struct **token, t_asset **start_cmd);
void	create_new_ast(t_asset **command);
int	assign_cmd_arg(t_token_struct **token, t_asset **start_cmd);
int	initialize_arguments(t_token_struct **token, t_asset **start_cmd, int i);
void	free_ast(t_asset *ast);
void	print_t_ast(t_asset *command, char *str_msg);
int	count_args(t_token_struct *token);
int	token_process(t_token_struct **cur_token, t_asset **cur_ast);
void	ft_printf_2d(char *str[], char *str_msg);
void	init_lexer_data(t_lexer_struct *lexer_dto, char *str);
int	add_args(t_token_struct **cur_token, t_asset *new_node);
void	free_arg(char **args);
char	*ft_strncat(char *s1, const char *s2, int n);

/* pipe functions */
void	handle_pipe(char **tokens);

void test_simple_command();
#endif