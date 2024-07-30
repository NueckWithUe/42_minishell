/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 16:34:50 by nnagel           ###   ########.fr       */
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

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	void			*data;
}	t_env;

char	**parser(char **tokens);
char	**lexer(char *input);

/* lexer utils */
int		ft_get_wc(char *str, char delimiter);
char	*ft_strtok(char *str, char delimiter);

/* pipes */
void	handle_pipe(t_env *envp, char **tokens);
void	get_command(char **tokens, char ***com1, char ***com2);
void	check_pid(pid_t pid);

/* cd */
int		cd(t_env *envp, char *path);

/* echo */
int		print_echo(char **tokens, int start);

/* env */
void	print_list(t_env *lst);
void	search_and_replace(t_env **start, char *to_replace);
void	search_and_remove(t_env **start, char *to_remove);

/* export */
// int		export(char **envp, char **tokens);
int		export(t_env *envp, char **tokens);
void	add_exports(t_env *envp, char **tokens);
t_env	*convert_env_to_list(char **envp);
void	ft_insert_at_end(t_env **start, char *data);

/* unset */
int		unset(t_env *envp, char **tokens);

/* general utils */
int		ft_strcomp(char *str1, char *str2);
int		array_size(char **array);
char	*convert_env(char *line);
void	ft_free_array(char **array1, char **array2);
#endif