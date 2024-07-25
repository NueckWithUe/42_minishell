/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:36:24 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/25 10:33:09 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_function(char **command)
{
	if (ft_strcomp())
}

static void	exe_cmd(pid_t pid, int *pipe_fd, char **command, int m)
{
	if (pid == 0)
	{
		dup2(pipe_fd[m], m);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_function(command);
		exit(EXIT_FAILURE);
	}
	// else if (pid == 0 && m == 1)
	// {
	// 	dup2(pipe_fd[0], STDIN_FILENO);
	// 	close(pipe_fd[1]);
	// 	close(pipe_fd[0]);
	// 	execve(, argv, NULL);
	// 	perror("execve");
	// 	exit(EXIT_FAILURE);
	// }
}

void	handle_pipe(char **tokens)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	char	**com1;
	char	**com2;

	get_command(tokens, &com1, &com2);
	ft_printf("%s\n", com1);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	check_pid(pid1);
	exe_cmd(pid1, pipe_fd, com1, 1);
	pid2 = fork();
	check_pid(pid2);
	exe_cmd(pid2, pipe_fd, com2, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
//still needs to execute all commands, also needs to be able to chain more pipes