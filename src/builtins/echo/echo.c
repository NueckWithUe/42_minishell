/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:54:36 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 18:02:32 by nnagel           ###   ########.fr       */
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
		if (ft_strcomp(tokens[i], "$?"))
		{
			ft_printf("latest return value"); //print return value; will be stored in semi global struct t_data
			i++;
			if (ft_strcomp(tokens[i], "EOFToken"))
				break ;
			else
				write(1, " ", 1);
		}
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
