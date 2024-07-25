/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:15:42 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/25 09:37:23 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
compares for equal strings
returns 1 if strings are equal*/
int	ft_strcomp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	array_size(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		;
	return (i);
}

char	*convert_env(char *line)
{
	char	*convert;

	convert = NULL;
	if (line[0] != '$')
		return (line);
	convert = ft_strdup(getenv(line + 1));
	if (!convert)
		return (NULL);
	return (convert);
}
