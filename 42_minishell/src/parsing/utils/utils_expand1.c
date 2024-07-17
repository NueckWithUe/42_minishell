/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:36:37 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/17 09:18:25 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_exit_status(int status_val, int *i, char **expand)
{
	char	*exit_status;
	char	*new_expand;
	int		res;

	exit_status = NULL;
	new_expand = NULL;
	res = 0;
	(*i)++;
	exit_status = ft_itoa(status_val);
	if (!exit_status)
		return (0);
	// new_expand = ft_strncat(*expand, exit_status, ft_strlen(status_val));
	new_expand = ft_strncat(*expand, exit_status, ft_strlen(exit_status));
	if (new_expand)
	{
		*expand = new_expand;
		res = 1;
	}
	// free_if_not_null(&exit_status);
	free_if_not_null(exit_status);
	if (!res)
		(*i)--;
	return (res);
}

