/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:54:36 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 17:08:23 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	print_echo(char **tokens, int start)
{
	int		i;
	char	*convert;

	i = start;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		convert = convert_env(tokens[i]);
		if (ft_strcomp(tokens[i + 1], "EOFToken"))
			ft_printf("%s", convert);
		else
			ft_printf("%s ", convert);
		if (tokens[i][0] == '$')
			free(convert);
		convert = NULL;
		i++;
	}
	if (start == 1)
		write(1, "\n", 1);
	return (0);
}
