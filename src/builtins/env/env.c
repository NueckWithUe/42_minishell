/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:02:20 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 18:52:06 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	search_and_replace(t_lst **start, char *to_replace)
{
	(void)start;
	(void)to_replace;
}

void	search_and_remove(t_lst **start, char *to_remove)
{
	t_lst	*temp;

	if (!ft_strncmp((*start)->data, to_remove, ft_strlen(to_remove)))
	{
		ft_remove_element(start);
		return ;
	}
	temp = *start;
	while (temp->next != *start)
	{
		if (!ft_strncmp(temp->data, to_remove, ft_strlen(to_remove)))
		{
			ft_remove_element(&temp);
			break ;
		}
		temp = temp->next;
	}
}

void	print_list(t_lst *lst)
{
	t_lst	*temp;

	temp = lst;
	while (temp->next != lst)
	{
		ft_printf("%s\n", temp->data);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->data);
}

t_lst	*convert_env_to_list(char **envp)
{
	t_lst	*env_lst;
	int		i;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		ft_insert_at_end(&env_lst, envp[i]);
		i++;
	}
	return (env_lst);
}
