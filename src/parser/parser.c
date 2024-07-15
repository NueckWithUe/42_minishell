/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:02:21 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/15 08:34:28 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_list(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("Token Nr. %d: [%s]\n", i, arr[i]);
		i++;
	}
}

char	**parser(char **tokens)
{
	print_list(tokens);
	return (tokens);
}
