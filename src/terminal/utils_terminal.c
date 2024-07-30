/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:57:50 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/25 02:31:06 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_cmd_not_found(t_minishell_struct *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("", 2);
	ft_putstr_fd(": command not found", 2);
	mini->cd_quite = 127;
}

static void	print_synt_not_found(char *str, t_minishell_struct *mini)
{
	(void)str;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd("", 2);
	ft_putendl_fd("\'", 2);
	mini->cd_quite = 258;
}

void	print_error(char *str, t_minishell_struct *mini)
{
	if (str[0] == '\"' && str[1] == '\"')
		print_cmd_not_found(mini);
	else if (ft_strncmp(str, "&&", 3) == 0)
		print_synt_not_found(str, mini);
}

static void	free_mini_resources(t_minishell_struct *min_data)
{
	if (min_data->envp)
		free_array(min_data->envp);
	if (min_data->token)
		free_list_of_token(min_data->token);
	if (min_data->commands)
		free_list_of_cmd(min_data->commands);
	if (min_data->home)
		free_if_not_null(&min_data->home);
	if (min_data->pwd)
		free_if_not_null(&min_data->pwd);
	if (min_data->readline)
		free_if_not_null(&min_data->readline);
}

void	free_mini(t_minishell_struct *mini)
{
	if (mini)
	{
		free_mini_resources(mini);
		mini = NULL;
	}
}
