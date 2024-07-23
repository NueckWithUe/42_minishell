/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:07:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/23 00:41:14 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	print_exports(char **envp)
{
	ft_printf("declare -x %s\n", envp[0]);
}

int	export(char **envp, char **tokens)
{
	int	i;

	i = 0;
	if (ft_strcomp(tokens[1], "EOFToken"))
		print_exports(envp);
	while (envp[i + 2] != NULL)
		i++;
	return (0);
}
