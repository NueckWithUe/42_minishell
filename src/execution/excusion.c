/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excusion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:57:06 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:16:18 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void	execute_child_process(t_minishell_struct *mini,
	char *path, int i, int lst_size)
{
	handle_files(mini, i, lst_size);
	executed_command(mini, path);
}

void	handle_execution_error(t_minishell_struct *mini)
{
	print_error_msg(mini->commands->args[0], 1, mini);
} */

/* void	executed_command(t_minishell_struct *mini, char *path)
{
	int	cmd_count;
	(void)path;
	if (ft_strncmp(mini->commands->args[0], "&&", 3) == 0)
		print_error(mini->commands->args[0], mini);
	else if (ft_strncmp(mini->commands->args[0], "exit", 5) == 0)
		ft_exit(mini);
	else
	{
		cmd_count = commands_count(mini->commands);
		if (cmd_count == 1)
			single_execution(mini);
		else if (cmd_count > 1)
			multiple_execution(mini);
		else
			handle_execution_error(mini);
	}
} */
/* 
void	cleanup_execution(t_minishell_struct *mini)
{
	if (mini->tokens)
		free_token_list(mini->tokens);
	if (mini->commands)
		free_cmd_list(mini->commands);
}

void	execution_manager(t_minishell_struct *mini)
{
	if (!mini || !mini->commands || !mini->commands->args || !mini->commands->args[0])
		handle_execution_error(mini);
	else
		execute_command(mini);
	cleanup_execution(mini);
}
 */