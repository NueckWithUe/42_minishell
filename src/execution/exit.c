/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 05:58:42 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:52:03 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_exit_non_numeric_argument(t_minishell_struct *mini)
{
	ft_putendl_fd("exit", 1);
	error_print_message("exit: ", mini->commands->args[1], 1, mini);
}

void	handle_exit_with_argument(t_minishell_struct *mini)
{
	ft_putendl_fd("exit", 1);
	system_exit(mini, ft_atoll(mini->commands->args[1]));
}

void	handle_exit_no_or_multiple_arguments(t_minishell_struct *mini)
{
	if (verify_envp_len(mini->commands->args) == 1)
	{
		ft_putendl_fd("exit", 1);
		system_exit(mini, mini->cd_quite);
	}
	else if (verify_envp_len(mini->commands->args) > 2
		&& is_string_numeric(mini->commands->args[1]))
		error_print_message("exit", NULL, 2, mini);
	else
		print_error_msg(mini->commands->args[0], 1, mini);
}

void	ft_exit(t_minishell_struct *mini)
{
	refresh_shell_level(mini, 0);
	if (ft_strncmp(mini->commands->args[0], "exit", 5) != 0)
		print_error_msg(mini->commands->args[0], 1, mini);
	else if (verify_envp_len(mini->commands->args) > 1
		&& !is_string_numeric(mini->commands->args[1]))
		handle_exit_non_numeric_argument(mini);
	else if (verify_envp_len(mini->commands->args) == 1
		|| verify_envp_len(mini->commands->args) > 2)
		handle_exit_no_or_multiple_arguments(mini);
	else
		handle_exit_with_argument(mini);
}
