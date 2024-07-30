/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:43:11 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 16:03:56 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parent_process_single(t_minishell_struct *mini,
	int pid, char *path, int *fd)
{
	int	status;
	int	wait_res;

	(void)fd;
	reset_input_output_single(mini, 0);
	wait_res = waitpid(pid, &status, 0);
	if (wait_res == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
	{
		mini->cd_quite = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		mini->cd_quite = WTERMSIG(status) + 128;
	}
	free_path(&path);
	g_global_signal = 0;
}

/* static void	handle_command_path(t_minishell_struct *mini, char **path)
{
	*path = ft_strdup(mini->commands->args[0]);
	*path = ft_find_path(mini, *path, 0);
}

static void	execute_command(t_minishell_struct *mini, char *path)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		stop("single exec fork() fail");
	else if (pid == 0)
		ft_execve(path, mini, NULL);
	parent_process_single(mini, pid, path, NULL);
}

void	single_execution(t_minishell_struct *mini)
{
	char	*path;

	path = NULL;
	g_global_signal = 1;
	start_signal_handler();
	mini->fds = set_fd(mini, 2, 0);
	manage_fd_for_execution(mini, 1);

	if (buildin_manager_check(mini))
	{
		buildin_manager(mini);
		reset_input_output_single(mini, 0);
		return ;
	}

	handle_command_path(mini, &path);
	if (!path)
		return ;
	execute_command(mini, path);
	stop_signal_handler();
} */
