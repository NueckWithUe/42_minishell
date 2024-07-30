/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:02:20 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 16:34:11 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	search_and_replace(t_env **start, char *to_replace)
{
	(void)start;
	(void)to_replace;
}

void	search_and_remove(t_env **start, char *to_remove)
{
	(void)start;
	(void)to_remove;
}

void	print_list(t_env *lst)
{
	t_env	*temp;

	temp = lst;
	while (temp->next != lst)
	{
		ft_printf("%s\n", temp->data);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->data);
}
