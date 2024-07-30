/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:56 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 20:27:14 by nnagel           ###   ########.fr       */
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

int	list_size(t_lst *lst)
{
	t_lst	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp->next != lst)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_free_list(t_lst *list)
{
	int	i;
	int	len;

	i = 0;
	len = list_size(list);
	while (i <= len)
	{
		free(list->data);
		free(list);
		list = list->next;
		i++;
	}
}