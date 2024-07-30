/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:40:52 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 16:03:56 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*update_shell_level(const char *old_num, int i)
{
	char	*new_num;
	int		old_level;

	if (correct_value(old_num) == 1)
		return (ft_strdup("0"));
	else if (correct_value(old_num) == 2)
		return (ft_strdup("1"));
	old_level = ft_atoi(old_num);
	if (i == 0)
	{
		new_num = ft_itoa(old_level - 1);
		if (ft_atoi(new_num) < 0)
		{
			free(new_num);
			return (ft_strdup("0"));
		}
	}
	else if (i == 1)
		new_num = ft_itoa(old_level + 1);
	else
		new_num = (ft_strdup("1"));
	return (new_num);
}

void	refresh_shell_level(t_minishell_struct *mini, int i)
{
	char	*old_num;
	char	*new_num;

	old_num = equal_value(ft_getenv(mini, "SHLVL"));
	if (!old_num)
		return ;
	new_num = update_shell_level(old_num, i);
	free_if_not_null(&old_num);
	old_num = ft_strjoin("SHLVL=", new_num);
	shelvl_free(mini, old_num, new_num);
}

void	initialiaz_envp(char *envp[], int len, t_minishell_struct *mini)
{
	int	index;

	index = -1;
	printf("Initial envp length: %d\n", len);
	if (!getenv_set(envp, "PWD"))
		len += 1;
	if (!getenv_set(envp, "OLDPWD"))
		len += 1;
	if (!getenv_set(envp, "SHLVL"))
		len += 1;
	printf("Adjusted envp length: %d\n", len);
	mini->envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!mini->envp)
	{
		printf("Error: malloc failed\n");
		free_mini(mini);
		exit(1);
	}
	envp_preparation(envp, index, mini, len);
}

static void	handle_readline_input(t_minishell_struct *mini)
{
	mini->readline = readline(mini->name_of_term);
	if (!mini->readline)
		return ;
	if (mini->readline[0] == '\0')
	{
		free_if_not_null(&mini->readline);
		return ;
	}
	add_history(mini->readline);
	if (is_ok_parsing(mini) && mini->commands
		&& mini->commands->args && mini->commands->args[0])
	//execution
	//else
	//	print_error(mini->readline, mini);
	free_if_not_null(&mini->readline);
	mini->readline = NULL;
}

void	terminal_initializ(t_minishell_struct *mini)
{
	while (1)
	{
		g_global_signal = 0;
		handle_readline_input(mini);
	}
	free_mini(mini);
	free(mini->name_of_term);
}
