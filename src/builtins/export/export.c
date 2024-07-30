/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:07:37 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/30 16:54:23 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// static char	*find_smallest_str(char **arr)
// {
// 	char	*smallest;
// 	int	i;

// 	i = 0;
// 	smallest = ft_strdup(arr[0]);
// 	while (arr[i])
// 	{
// 		if (ft_strncmp(arr[i], smallest, sizeof(long)) < 1)
// 		{
// 			free(smallest);
// 			smallest = ft_strdup(arr[i]);
// 		}
// 		i++;
// 	}
// 	return (smallest);
// }

// if s1 bigger than s2 ft_strncmp returns positive. "B" compared with "A" returns 1, "A" compared with "B" returns -1

static int	list_size(t_lst *lst)
{
	t_lst	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp->next != lst)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

static char	**sort_ascend(t_lst *envp)
{
	t_lst	*temp;
	char	**sorted;
	int		i;

	i = 0;
	sorted = malloc(sizeof(char *) * list_size(envp) + 1);
	temp = envp;
	// sorted[0] = find_smallest_str(envp);
	while (temp->next != envp)
	{
		sorted[i] = ft_strdup(temp->data);
		i++;
		temp = temp->next;
	}
	return (sorted);
}
// will soon be sorted properly


static void	print_exports(t_lst *envp)
{
	char	**sorted;
	int		i;

	sorted = NULL;
	sorted = sort_ascend(envp);
	i = 0;
	while (sorted[i + 1])
	{
		ft_printf("declare -x %s\n", sorted[i]);
		i++;
	}
}

int	export(t_lst *envp, char **tokens)
{
	int	i;

	i = 0;
	if (ft_strcomp(tokens[1], "EOFToken"))
	{
		print_exports(envp);
	}
	else
	{
		add_exports(envp, tokens);
	}
	return (0);
}
