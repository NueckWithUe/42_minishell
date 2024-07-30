/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 04:16:04 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 16:03:56 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_for_children_recursive(t_minishell_struct *mini,
	int i, int lst_size)
{
	int	status;

	if (i >= lst_size)
		return ;
	waitpid(mini->pids[i], &status, 0);
	if (WIFEXITED(status))
		mini->cd_quite = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		mini->cd_quite = WTERMSIG(status) + 128;
	wait_for_children_recursive(mini, i + 1, lst_size);
}

void	wait_children(t_minishell_struct *mini, int lst_size)
{
	wait_for_children_recursive(mini, 0, lst_size);
}

void	cleanup_resources(t_minishell_struct *mini, int lst_size)
{
	free(mini->pids);
	free_fd(mini->fds, lst_size);
	g_global_signal = 0;
	stop_signal_handler();
}

void	synchronize_with_children(t_minishell_struct *mini, int lst_size)
{
	close_fds(mini->fds, lst_size);
	wait_children(mini, lst_size);
	cleanup_resources(mini, lst_size);
}
