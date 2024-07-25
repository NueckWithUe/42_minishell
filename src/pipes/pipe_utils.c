/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:12:18 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/25 10:16:02 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../../../include/minishell.h>

static int	size_before_pipe(char **tokens, int a)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (!ft_strcomp(tokens[i], "|"))
		i++;
	if (a)
	{
		i++;
		while (!ft_strcomp(tokens[i], "EOFToken"))
		{
			i++;
			j++;
		}
		return (j);
	}
	return (i);
}

void	get_command(char **tokens, char ***com1, char ***com2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*com1 = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 0) + 1);
	*com2 = (char **)malloc(sizeof(char *) * size_before_pipe(tokens, 1) + 1);
	while (!ft_strcomp(tokens[i], "|"))
	{
		(*com1)[i] = ft_strdup(tokens[i]);
		i++;
	}
	(*com1)[i] = NULL;
	i++;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		(*com2)[j] = ft_strdup(tokens[i]);
		i++;
		j++;
	}
	(*com2)[j] = NULL;
}

void	check_pid(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
