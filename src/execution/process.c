/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 04:08:36 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:40:01 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	retrieve_command_path(t_minishell_struct *mini, char **path)
{
	if (!buildin_manager_check(mini))
	{
		*path = ft_find_path(mini, mini->commands->args[0], 0);
		if (!*path)
			return ;
	}
}

/* void	handle_child_execution(t_minishell_struct *mini,
	char *path, int i, int lst_size)
{
	execute_child_process(mini, path, i, lst_size);
} */

void	execute_multiple_children(t_minishell_struct *mini, int i, int lst_size)
{
	char	*path;

	(void)i;
	(void)lst_size;
	path = NULL;
	retrieve_command_path(mini, &path);
	//handle_child_execution(mini, path, i, lst_size);
}

int	iterate_list(t_asset *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

int	commands_count(t_asset *lst)
{
	if (!lst)
		return (0);
	return (iterate_list(lst));
}
