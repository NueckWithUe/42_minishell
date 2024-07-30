/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:56 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 17:39:16 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_insert_at_end(t_lst **start, char *data)
{
	t_lst	*new_data;
	t_lst	*last;

	new_data = malloc(sizeof(t_lst));
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

void	ft_insert_begin(t_lst **start, char *data)
{
	t_lst	*new_env;
	t_lst	*last;

	last = (*start)->prev;
	new_env = malloc(sizeof(t_lst));
	new_env->data = ft_strdup(data);
	new_env->next = *start;
	new_env->prev = last;
	last->next = new_env;
	(*start)->prev = new_env;
	(*start) = new_env;
}
