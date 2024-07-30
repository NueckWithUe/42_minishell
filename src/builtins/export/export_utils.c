/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:56 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 16:34:06 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_insert_at_end(t_env **start, char *data)
{
	t_env	*new_data;
	t_env	*last;

	new_data = malloc(sizeof(t_env));
	new_data->data = ft_strdup(data);
	if (*start == NULL)
	{
		new_data->prev = new_data;
		new_data->next = new_data->prev;
		*start = new_data;
		return ;
	}
	last = (*start)->prev;
	new_data->next = *start;
	(*start)->prev = new_data;
	new_data->prev = last;
	last->next = new_data;
}

t_env	*convert_env_to_list(char **envp)
{
	t_env	*env_lst;
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
