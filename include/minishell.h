/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:09 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/25 10:16:57 by nnagel           ###   ########.fr       */
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

char	**parser(char **tokens);
char	**lexer(char *input);

/* lexer utils */
int		ft_get_wc(char *str, char delimiter);
char	*ft_strtok(char *str, char delimiter);

/* pipes */
void	handle_pipe(char **tokens);
void	get_command(char **tokens, char ***com1, char ***com2);
void	check_pid(pid_t pid);

/* cd */
int		cd(char **envp, char *path);

/* echo */
int		print_echo(char **tokens, int start);

/* env */
int		print_arr(char **arr);

/* export */
int		export(char **envp, char **tokens);

/* unset */
int		unset(char ***envp, char **tokens);

/* general utils */
int		ft_strcomp(char *str1, char *str2);
int		array_size(char **array);
char	*convert_env(char *line);
#endif