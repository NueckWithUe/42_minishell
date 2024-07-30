/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:07:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/29 13:34:23 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char **sort_ascend(char **envp)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = malloc(sizeof(char *) * array_size(envp) + 1);
	while (envp[i])
	{
		sorted[i] = ft_strdup(envp[i]);
		i++;
	}
	return (sorted);
	//go through string and search for the lowest value. Then search for the lowest value in relation to the current value
}

static void	print_exports(char **envp)
{
	char	**sorted;
	int		i;

	sorted = sort_ascend(envp);
	i = 0;
	while (sorted[i])
	{
		ft_printf("declare\t-x %s\n", sorted[i]);
		i++;
	}
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
