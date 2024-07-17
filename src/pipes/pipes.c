/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:36:24 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/17 10:04:43 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	size_before_pipe(char **tokens, int a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_strcomp(tokens[i], "|"))
		i++;
	if (a)
	{
		i++;
		while (!ft_strcomp(tokens[i], "EOFToken"))
		{
			i++;
			j++;
		}
		return (j);
	}
	return (i);
}

static void	get_command(char **tokens, char ***com1, char ***com2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*com1 = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 0) + 1);
	*com2 = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 1) + 1);
	while (!ft_strcomp(tokens[i], "|"))
	{
		(*com1)[i] = ft_strdup(tokens[i]);
		i++;
	}
	(*com1)[i] = NULL;
	i++;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		(*com2)[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	(*com2)[j] = NULL;
}

static void	check_pid(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

static void	exe_cmd(pid_t pid, int *pipe_fd, char **argv, char *path, int m)
{
	if (pid == 0)
	{
		dup2(pipe_fd[m], m);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(path, argv, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	// else if (pid == 0 && m == 1)
	// {
	// 	dup2(pipe_fd[0], STDIN_FILENO);
	// 	close(pipe_fd[1]);
	// 	close(pipe_fd[0]);
	// 	execve(path, argv, NULL);
	// 	perror("execve");
	// 	exit(EXIT_FAILURE);
	// }
}

// static char	*get_path(char *command)
// {
// 	char	*path;

// 	path = NULL;
// 	if (ft_strcomp(command, "echo"))
// 		path = ft_strjoin("/bin/echo", command);
// 	return (path);
// }

void	handle_pipe(char **tokens)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	char	**argv1;
	char	**argv2;
	char	*path;

	get_command(tokens, &argv1, &argv2);
	path = ft_strjoin("/bin/", argv1[0]);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	check_pid(pid1);
	exe_cmd(pid1, pipe_fd, argv1, path, 1);
	free(path);
	pid2 = fork();
	check_pid(pid2);
	path = ft_strjoin("/usr/bin/", argv2[0]);
	exe_cmd(pid2, pipe_fd, argv2, path, 0);
	free(path);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
//still needs to execute all commands, also needs to be able to chain more pipes