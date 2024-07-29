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
	int		j;

	i = 0;
	j = 0;
	sorted = malloc(sizeof(char *) * array_size(envp) + 1);
	while (envp[i])
	{
		i++;
	}
	return (sorted);
}

static void	print_exports(char **envp)
{
	char	**sorted;
	int		i;

	sorted = sort_ascend(envp);
	i = 0;
	while (sorted[i])
	{
		ft_printf("declare -x %s\n", sorted[i]);
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

// static char *get_first_line(char **arr)
// {
// 	int i;
// 	int index_smallest;

// 	i = 1;
// 	index_smallest = 0;
// 	while (arr[i])
// 	{
// 		// if (ft_strncmp(arr[i], arr[index_smallest], sizeof(long)));

// 		i++;
// 	}
// 	return (arr[index_smallest]);
// }

// static void sort_ascend(char **arr, char ***sorted)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	if (*sorted == NULL)
// 		*sorted = malloc(sizeof(char *) * size_array(arr) + 1);
// 	while (arr[i])
// 	{
// 		(*sorted)[j] = ft_strdup(arr[i]);
// 		j++;
// 		i++;
// 	}
// 	if (size_array(*sorted) != size_array(arr))
// 		sort_ascend(arr, sorted);
// }

// static void compare_strings(char **arr)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (arr[i])
// 	{
// 		while (arr[j])
// 		{
// 			if (i == j)
// 				j++;
// 			printf("%c compared with %c: %d\n", arr[i][0], arr[j][0], ft_strncmp(arr[i], arr[j], sizeof(long)));
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 	}
// }

// int main()
// {
// 	char **arr;
// 	char **sorted;

// 	sorted = NULL;
// 	arr = malloc(sizeof(char *) * 3);
// 	arr[0] = ft_strdup("Test");
// 	arr[1] = ft_strdup("Sorting");
// 	arr[2] = ft_strdup("Arrays");
// 	compare_strings(arr);
// 	sort_ascend(arr, &sorted);
// 	print_array(arr);
// 	write(1, "\n", 1);
// 	print_array(sorted);
// }