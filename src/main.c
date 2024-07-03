/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/03 12:29:21 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	char	*ret;

	ret = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	ret = readline(">> ");
	while (ret && ret[0] == '\0')
		ret = readline(">> ");
	lexer(ret);
	return (0);
}
