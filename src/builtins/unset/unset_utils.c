/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:23:17 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 18:25:43 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_remove_element(t_lst **start)
{
	t_lst	*curr;
	t_lst	*last;

	curr = *start;
	if ((*start)->prev == (*start))
	{
		free((*start));
		(*start) = NULL;
		return ;
	}
	last = (*start)->prev;
	*start = (*start)->next;
	last->next = (*start);
	(*start)->prev = last;
	free(curr);
}
