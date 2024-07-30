/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exports.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:02:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 20:22:52 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_exports(char ***envp, char **tokens)
{
	int	i;

	i = 1;
	(void)envp;
	while (ft_strncmp(tokens[i], "EOFToken", 8))
	{
		if (ft_strchr(tokens[i], '='))
		{
			//insert varaible at beginning of envp
		}
		i++;
	}
}
