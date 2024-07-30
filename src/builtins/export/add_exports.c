/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exports.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 16:54:23 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_exports(t_lst *envp, char **tokens)
{
	int	i;

	i = 1;
	while (ft_strncmp(tokens[i], "EOFToken", 8))
	{
		if (ft_strchr(tokens[i], '='))
		{
			ft_printf("%s should be added to env\n", tokens[i]);
			ft_insert_at_end(&envp, tokens[i]);
		}
		i++;
	}
}
