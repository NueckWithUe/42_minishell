/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:54:36 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/22 20:57:24 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	print_echo(char **tokens, int start)
{
	int	i;

	i = start;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		if (ft_strcomp(tokens[i + 1], "EOFToken"))
			ft_printf("%s", tokens[i]);
		else
			ft_printf("%s ", tokens[i]);
		i++;
	}
	if (start == 1)
		write(1, "\n", 1);
	return (0);
}
