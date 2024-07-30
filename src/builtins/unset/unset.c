/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:08:02 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 18:53:09 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset(t_lst **envp, char **tokens)
{
	int	i;

	i = 0;
	while (!ft_strcomp(tokens[++i], "EOFToken"))
		search_and_remove(envp, tokens[i]);
	return (0);
}
