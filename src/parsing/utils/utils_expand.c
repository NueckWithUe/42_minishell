/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 09:05:35 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/25 02:31:06 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	copy_elmt(char **dest, char **src, int *idx)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[*idx] = ft_strdup(src[i]);
		(*idx)++;
		i++;
	}
}

static void	copy_idx(char **dest, char **src, int *idx, int stop)
{
	int	i;

	i = 0;
	while (src && src[i] && i < stop)
	{
		dest[*idx] = ft_strdup(src[i]);
		(*idx)++;
		i++;
	}
}

static int	verify_envp_length(char *envp[])
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
		i++;
	return (i);
}

char	**arry_concat(char **array_a, char **array_b, int start, int *read_flag)
{
	int		len_1;
	int		len_2;
	int		i;
	char	**res;

	len_1 = verify_envp_length(array_a);
	len_2 = verify_envp_length(array_b);
	res = ft_calloc((len_1 + len_2 + 1), sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	copy_idx(res, array_a, &i, start);
	copy_elmt(res, array_b, &i);
	while (array_a && array_a[start])
	{
		res[i] = ft_strdup(array_a[start]);
		i++;
		start++;
	}
	res[i] = NULL;
	free_array(array_a);
	free_array(array_b);
	*read_flag = 0;
	return (res);
}

int	envp_string_end_check(int charact)
{
	return ((charact >= '0' && charact <= '9')
		|| (charact >= 'A' && charact <= 'Z')
		|| (charact >= '0' && charact <= 'a')
		|| charact == '_');
}
