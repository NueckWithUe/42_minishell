/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:00:03 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:43:28 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_fd_dup(int old_fd, int new_fd, const char *error_msg)
{
	if (dup2(old_fd, new_fd) == -1)
		stop(error_msg);
	printf("fd %d -> %d\n", old_fd, new_fd);
}

void	close_fd(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO)
	{
		close(fd);
		printf("Closed fd: %d\n", fd);
	}
}

void	manage_fd_for_execution(t_minishell_struct *mini, int i)
{
	if (mini->commands->fd_infile != STDIN_FILENO)
	{
		handle_fd_dup(mini->fds[i][0], STDIN_FILENO, "Dup 7");
		close_fd(mini->commands->fd_infile);
	}
	if (mini->commands->fd_outfile != STDOUT_FILENO)
	{
		handle_fd_dup(mini->fds[i][1], STDOUT_FILENO, "Dup 8");
		close_fd(mini->commands->fd_outfile);
	}
}

void	reset_input_output_single(t_minishell_struct *mini, int i)
{
	if (mini->fds[i][0] != -1)
		dup2(mini->fds[i][0], STDIN_FILENO);
	if (mini->fds[i][1] != -1)
		dup2(mini->fds[i][1], STDOUT_FILENO);
	free_fd(mini->fds, 2);
}

void	ft_execve(char *path, t_minishell_struct *mini, int *fd)
{
	(void)fd;
	if (!path || !mini || !mini->commands || !mini->envp)
	{
		fprintf(stderr, "Invalid arguments provided to ft_execve.\n");
		exit(EXIT_FAILURE);
	}
	if (execve(path, mini->commands->args, mini->envp) == -1)
	{
		print_error_msg(mini->commands->args[0], 1, mini);
		free_if_not_null(&path);
		mini->cd_quite = 127;
		exit(mini->cd_quite);
	}
	free_mini(mini);
	exit(EXIT_SUCCESS);
}
