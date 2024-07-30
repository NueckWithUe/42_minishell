/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 22:48:25 by nnagel           ###   ########.fr       */
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

# define DEBUG 0
# define BUFFER_SIZE 1024
# include "libft.h"

extern int	g_global_signal;

typedef struct s_host
{
	char	**argumt_cmd;
	char	*result;
}	t_host;

typedef enum s_type
{
	WORD,
	PIPE,
	APP_OUT,
	HEAD_DOC,
	EOL,
	ERROR
}	t_type;

typedef struct s_lexer_struct
{
	char	*line;
	int		position;
	int		dbl_quote;
	int		spl_quote;
}	t_lexer_struct;


typedef struct s_token_struct
{
	t_type					type;
	char					*value;
	struct s_token_struct	*next;
	struct s_token_struct	*prev;
}	t_token_struct;

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
	int				**fds;
	char			*readline;
	char			*pwd;
	char			*home;
	char			**envp;
	int				*pids;
	int				cd_quite;
	int				fd_input;
	int				fd_output;
	t_token_struct	*token;
	t_asset			*commands;
	pid_t			*pid;
	int				last_exit_status;
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
t_token_struct	*handle_less_than(t_lexer_struct *lexer, char next_char);
t_token_struct	*handle_greater_than(t_lexer_struct *lexer, char next_char);
// lexical
void			print_token(t_token_struct *token, const char *msg);
void			print_list_of_token(t_token_struct *list, const char *msg);
int				tokenize_line(t_lexer_struct *lexer_data,
					t_minishell_struct *mini);
int				is_lexically_valid(t_minishell_struct *mini);
void			free_if_not_null(char **str);
void			free_list_of_token(t_token_struct *token);
int				is_lexically_valid(t_minishell_struct *mini);
int				tokenize_line(t_lexer_struct *lexer_data,
					t_minishell_struct *mini);
void			print_token(t_token_struct *token, const char *msg);
int				validate_syntax(t_minishell_struct *mini);
int				pipe_sytx_error(t_token_struct *token);
int				redirection_sytx_error(t_token_struct *token);
int				generat_asset_cmd_instruct(t_minishell_struct *mini);
int				insert_new_ast_node(t_token_struct **token,
					t_asset **start_cmd);
void			create_new_ast(t_asset **command);
int				assign_cmd_arg(t_token_struct **token, t_asset **start_cmd);
int				initialize_arguments(t_token_struct **token,
					t_asset **start_cmd, int i);
void			free_ast(t_asset *ast);
void			print_t_asset(t_asset *command, char *str_msg);
int				count_args(t_token_struct *token);
int				token_process(t_token_struct **cur_token, t_asset **cur_ast);
void			ft_printf_2d(char *str[], char *str_msg);
void			init_lexer_data(t_lexer_struct *lexer_dto, char *str);
int				add_args(t_token_struct **cur_token, t_asset *new_node);
void			free_arg(char **args);
char			*ft_strncat(char *s1, const char *s2, int n);
int				envp_string_end_check(int charact);
int				handle_expansion(t_minishell_struct *mini, const char *arg,
					int *i, char **expand);
char			*double_quotes(t_minishell_struct *mini,
					const char *args, int *i, char **expand);
char			*single_quotes_handler(const char *args, int *i, char **expand);
int				append_char(char **expand, char c);
char			**arry_concat(char **array_a, char **array_b,
					int start, int *read_flag);
void			free_array(char **args);
char			*get_env_value(char **envp, char *var_name);
char			*extract_env_var(const char *arg, int *i);
int				passed_expasion(t_minishell_struct *mini);
int				write_herdoc(int fd, char *seperator,
					t_minishell_struct *mini, int j);
int				handle_herdoc(int fd, char *seprator,
					t_minishell_struct *mini, int j);
int				handle_input_red(t_asset *beg_cmd,
					t_minishell_struct *mini, int *i);
int				handle_ouput_red(t_asset *beg_cmd, int *i);
int				is_ok_parsing(t_minishell_struct *mini);
int				check_file_access(const char *filename,
					t_minishell_struct *mini);
void			push_at_front(char **args, int *postion, int n);
int				write_herdoc(int fd, char *seperator,
					t_minishell_struct *mini, int j);
int				check_expansion(t_minishell_struct *mini, char **args,
					int *read_fl);
int				check_exit_status(int status_val, int *i, char **expand);
int				verify_file_access(const char *path);
int				check_file_type(const char *path);
int				write_append_to_file(t_asset *beg_cmd, int *i);
int				process_heredoc_from_file(t_asset *beg_cmd,
					t_minishell_struct *mini, int *i);
int				handle_redirection_input(t_minishell_struct *mini);
void			terminal_initializ(t_minishell_struct *mini);
void			free_mini(t_minishell_struct *mini);
void			free_list_of_cmd(t_asset *commands);
void			shelvl_free(t_minishell_struct *mini,
					char *old_num, char *new_num);
void			refresh_shell_level(t_minishell_struct *mini, int i);
int				correct_value(const char *str);
int				handle_env_var(t_minishell_struct *mini,
					const char *arg, int *i, char **expand);
char			*expansion_status(t_minishell_struct *mini,
					const char *args, char **expand, int *read_fl);
char			*equal_value(const char *env);
void			locate_env_var(char **envp, const char *name,
					const char *new_value);
void			init_minishell(t_minishell_struct *mini, char *envp[]);
int				getenv_set(char **envp, char *to_get);
char			*ft_getenv(t_minishell_struct *mini, char *to_get);
int				env_beg_with_str(char *envp[], const char *str);
void			initialiaz_envp(char *envp[],
					int len, t_minishell_struct *mini);
int				verify_envp_len(char *envp[]);
void			envp_preparation(char *envp[], int idx,
					t_minishell_struct *mini, int len);
int				check_envp(char **envp, const char *var);
char			*find_pwd_in_getcwd(void);
char			*locate_home_getcwd(void);
void			init_hostname(t_host *hostname, const char *str);
void			get_hostname_child_process(t_host *t_hostname);
char			*get_formated(char *user, char *host, char *pwd);
char			*get_name_of_term_formated(char *envp[]);
void			terminal_initializ(t_minishell_struct *mini);
void			handle_error(const char *msg);
char			*gett_env_value(char *envp[], const char *key);
// signals

void			stop_signal_handler(void);
void			start_signal_handler(void);
void			sigquit_process(int signal);
void			sigint_process(int signal);
int				terminal_ctrl_proces(void);

//EXC
void			reset_input_output_single(t_minishell_struct *mini, int i);
void			free_fd(int **fd, int size);
void			parent_process_single(t_minishell_struct *mini,
					int pid, char *path, int *fd);
void			ft_execve(char *path, t_minishell_struct *mini, int *fd);
void			free_path(char **path);
void			print_error_msg(char *message, int c, t_minishell_struct *mini);
char			*init_string(t_minishell_struct *mini, char *s);
char			*init_path(t_minishell_struct *mini, char *s);
void			manage_fd_for_execution(t_minishell_struct *mini, int i);
void			stop(const char *msg);
void			single_execution(t_minishell_struct *mini);
char			*ft_find_path(t_minishell_struct *mini, char *arg, int i);
int				buildin_manager_check(t_minishell_struct *mini);
int				**set_fd(t_minishell_struct *mini, int lst_size, int flag);
void			buildin_manager(t_minishell_struct *mini);
void			multiple_execution(t_minishell_struct *mini);
void			synchronize_with_children(t_minishell_struct *mini,
					int lst_size);
void			wait_for_children(t_minishell_struct *mini, int i,
					int lst_size);
void			execute_child_process(t_minishell_struct *mini,
					char *path, int i, int lst_size);
void			wait_children(t_minishell_struct *mini, int lst_size);
void			ft_execve(char *path, t_minishell_struct *mini, int *fd);
void			reset_input_output_single(t_minishell_struct *mini, int i);
void			manage_fd_for_execution(t_minishell_struct *mini, int i);
void			close_fd(int fd);
void			handle_fd_dup(int old_fd, int new_fd, const char *error_msg);
void			close_fds(int **fd, int size);
int				ft_strcmp(const char *s1, const char *s2);
int				is_string_numeric(char *s);
void			error_print_message(char *message1, char *message2, int c,
					t_minishell_struct *mini);
void			system_exit(t_minishell_struct *mini, int c);
void			ft_exit(t_minishell_struct *mini);
long long		ft_atoll(const char *str);
void			execute_multiple_children(t_minishell_struct *mini,
					int i, int lst_size);
int				commands_count(t_asset *lst);
int				buildin_manager_check_recursive(t_minishell_struct *mini,
					int index);
void			print_error(char *str, t_minishell_struct *mini);
void			reset_input_output(t_minishell_struct *mini, int size);
void			handle_files(t_minishell_struct *mini, int i, int lst_size);
void			execute_child_process(t_minishell_struct *mini,
					char *path, int i, int lst_size);
void			executed_command(t_minishell_struct *mini, char *path);

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	void			*data;
}	t_lst;

/* pipes */
void	handle_pipe(char ***envp, char **tokens);
void	get_command(char **tokens, char ***com1, char ***com2);
void	check_pid(pid_t pid);

/* cd */
int		cd(char ***envp, char *path);

/* echo */
int		print_echo(char **tokens, int start);

/* env */
void	print_envp(char **envp);
void	search_and_remove(char ***start, char *to_remove);

/* export */
int		export(char ***envp, char **tokens);
void	add_exports(char ***envp, char **tokens);
t_lst	*convert_env_to_list(char **envp);
void	ft_insert_at_end(t_lst **start, char *data);
void	ft_free_list(t_lst *list);
int		list_size(t_lst *lst);

/* unset */
int		unset(char ***envp, char **tokens);

/* general utils */
int		ft_strcomp(char *str1, char *str2);
int		array_size(char **array);
char	*convert_env(char *line);
void	ft_free_array(char **array1, char **array2);
#endif