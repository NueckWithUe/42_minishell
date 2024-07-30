/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 03:59:34 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 16:03:56 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds_recursive(int **fds, int i, int size)
{
	if (i >= size)
	{
		return ;
	}
	close(fds[i][0]);
	close(fds[i][1]);
	close_fds_recursive(fds, i + 1, size);
}

void	free_fds_recursive(int **fds, int i, int size)
{
	if (i >= size)
	{
		return ;
	}
	free(fds[i]);
	free_fds_recursive(fds, i + 1, size);
}

void	fork_child_processes(t_minishell_struct *mini,
	t_asset *cmd, int i, int lst_size)
{
	if (i >= lst_size || !cmd)
	{
		return ;
	}
	mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		stop("Fork failed");
	}
	if (mini->pids[i] == 0)
	{
		execute_multiple_children(mini, i, lst_size);
	}
	fork_child_processes(mini, cmd->next, i + 1, lst_size);
}

void	wait_for_children(t_minishell_struct *mini, int i, int lst_size)
{
	int	status;

	if (i >= lst_size)
	{
		return ;
	}
	waitpid(mini->pids[i], &status, 0);
	if (WIFEXITED(status))
	{
		mini->cd_quite = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		mini->cd_quite = WTERMSIG(status) + 128;
	}
	wait_for_children(mini, i + 1, lst_size);
}

void	multiple_execution(t_minishell_struct *mini)
{
	int	lst_size;

	start_signal_handler();
	lst_size = commands_count(mini->commands);
	mini->fds = set_fd(mini, lst_size, 1);
	mini->pids = malloc(lst_size * sizeof(int));
	if (!mini->pids)
		stop("malloc pids");
	fork_child_processes(mini, mini->commands, 0, lst_size);
	wait_for_children(mini, 0, lst_size);
	close_fds_recursive(mini->fds, 0, lst_size);
	free(mini->pids);
	free_fds_recursive(mini->fds, 0, lst_size);
	free(mini->fds);
	g_global_signal = 0;
	stop_signal_handler();
}
