/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:36:13 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/22 09:56:16 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_saned_path(char *path)
{
	char	*saned_path;
	int		i;
	int		j;

	saned_path = malloc(ft_strlen(path));
	if (!saned_path)
		return (NULL);
	i = 1;
	j = 0;
	while (path[i])
	{
		saned_path[j] = path[i];
		i++;
		j++;
	}
	saned_path[j] = '\0';
	return (saned_path);
}

int	cd(char *path)
{
	char	*alt_path;
	char	*saned_path;

	if (path == NULL)
		return (1);
	if (ft_strcomp(path, "-"))
		alt_path = ft_strdup(getenv("OLDPWD"));
	else if (ft_strcomp(path, "EOFToken"))
		alt_path = ft_strdup(getenv("HOME"));
	else if (path[0] == '~')
	{
		if (path[1] == '\0')
			alt_path = ft_strdup(getenv("HOME"));
		else
		{
			saned_path = get_saned_path(path);
			alt_path = ft_strjoin(getenv("HOME"), saned_path);
			free(saned_path);
		}
	}
	else
		alt_path = ft_strdup(path);
	if (chdir(alt_path) == -1)
	{
		ft_printf("Error.\nDirectory '%s' not found.\n", alt_path);
		free(alt_path);
		return (1);
	}
	free(alt_path);
	return (0);
}
