/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:08:02 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 20:06:57 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unset(char ***envp, char **tokens)
{
	int	i;

	i = 0;
	while (!ft_strcomp(tokens[++i], "EOFToken"))
		search_and_remove(envp, tokens[i]);
	return (0);
}
