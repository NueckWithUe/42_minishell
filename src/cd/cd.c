/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:36:13 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/17 11:42:19 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(char *path)
{
	DIR	*dirp;

	if (path == NULL)
		return (1);
	dirp = opendir(path);
	closedir(dirp);
	return (0);
}
