/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:08:02 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 17:55:44 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset(t_lst **envp, char **tokens)
{
	(void)envp;
	if (ft_strcomp(tokens[1], "EOFToken"))
		return (0);
	return (0);
}
