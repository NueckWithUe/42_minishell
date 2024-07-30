/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:50:29 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:39:18 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(const char *cmd, const char *builtin)
{
	return (ft_strcmp(cmd, builtin) == 0);
}

int	buildin_manager_check_recursive(t_minishell_struct *mini, int index)
{
	static const char	*builtins[] = {"cd", "pwd", "echo",
		"env", "unset", "export"};

	if (index >= 6)
		return (0);
	if (check_builtin(mini->commands->args[0], builtins[index]))
		return (1);
	return (buildin_manager_check_recursive(mini, index + 1));
}

int	buildin_manager_check(t_minishell_struct *mini)
{
	return (buildin_manager_check_recursive(mini, 0));
}

void	system_exit(t_minishell_struct *mini, int c)
{
	ft_putendl_fd("exit", 1);
	free_mini(mini);
	if (mini && mini->name_of_term)
	{
		free(mini->name_of_term);
		mini->name_of_term = NULL;
	}
	exit(c);
}

long long	ft_atoll(const char *str)
{
	long long	result;
	long long	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
