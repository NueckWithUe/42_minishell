/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:43:46 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/27 07:44:05 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_input_output(t_minishell_struct *mini, int size)
{
	close_fds(mini->fds, size);
	if (mini->commands->fd_infile != STDIN_FILENO)
	{
		if (dup2(mini->commands->fd_infile, STDIN_FILENO) == -1)
		{
			perror("Duplication d'entrée standard a échoué");
			exit(EXIT_FAILURE);
		}
		close(mini->commands->fd_infile);
	}
	if (mini->commands->fd_outfile != STDOUT_FILENO)
	{
		if (dup2(mini->commands->fd_outfile, STDOUT_FILENO) == -1)
		{
			perror("Duplication de sortie standard a échoué");
			exit(EXIT_FAILURE);
		}
		close(mini->commands->fd_outfile);
	}
}

void	close_fds(int **fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (close(fd[i][0]) == -1)
			perror("Error closing fd[i][0]");
		if (close(fd[i][1]) == -1)
			perror("Error closing fd[i][1]");
		i++;
	}
}

void	handle_dup2(int oldfd, int newfd, const char *msg)
{
	if (dup2(oldfd, newfd) == -1)
		stop(msg);
}

void	handle_files(t_minishell_struct *mini, int i, int lst_size)
{
	if (i == 0)
		handle_dup2(mini->fds[i][1], STDOUT_FILENO, "Dup 1");
	else if (mini->commands->next == NULL)
		handle_dup2(mini->fds[i - 1][0], STDIN_FILENO, "Dup 2");
	else
	{
		handle_dup2(mini->fds[i - 1][0], STDIN_FILENO, "Dup 3");
		handle_dup2(mini->fds[i][1], STDOUT_FILENO, "Dup 4");
	}
	reset_input_output(mini, lst_size);
}

/* void	(t_minishell_struct *mini, char *path)
{
	if (buildin_manager_check(mini))
	{
		buildin_manager(mini);
		free_if_not_null(&path);
		exit(EXIT_SUCCESS);
	}
	if (execve(path, mini->commands->args, mini->envp) == -1)
	{
		free_if_not_null(&path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->commands->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	free_mini(mini);
	exit(EXIT_SUCCESS);
}

 */