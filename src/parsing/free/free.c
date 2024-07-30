/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 03:35:33 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:54:14 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_list_of_cmd(t_asset *cmd)
{
	t_asset	*tmp;

	while (cmd)
	{
		tmp = cmd;
		if (cmd->args)
		{
			printf("Freeing cmd args: %p\n", (void *)cmd->args);
			free_array(cmd->args);
		}
		cmd = cmd->next;
		printf("Freeing cmd struct: %p\n", (void *)tmp);
		free(tmp);
	}
}

void	shelvl_free(t_minishell_struct *mini,
	char *find_old_num, char *find_new_num)
{
	if (mini && mini->envp && find_old_num)
	{
		locate_env_var(mini->envp, "SHLVL=", find_old_num);
	}
	if (find_new_num)
	{
		free_if_not_null(&find_new_num);
	}
	if (find_old_num)
	{
		free_if_not_null(&find_old_num);
	}
}

void	free_hostname(t_host *hostname)
{
	int	i;

	if (hostname->argumt_cmd)
	{
		i = 0;
		while (hostname->argumt_cmd[i])
		{
			free_if_not_null(&hostname->argumt_cmd[i]);
			i++;
		}
		free_if_not_null(&hostname->argumt_cmd[1]);
		free_array(hostname->argumt_cmd);
	}
	if (hostname->result)
		free_if_not_null(&hostname->result);
}

void	handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_arg(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}
