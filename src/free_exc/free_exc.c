/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 06:47:35 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/26 04:55:15 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_fd_recursive(int **fds, int size, int index)
{
	if (index >= size)
	{
		free(fds);
		return ;
	}
	if (fds[index])
	{
		if (fds[index][0] != -1)
			close(fds[index][0]);
		if (fds[index][1] != -1)
			close(fds[index][1]);
		free(fds[index]);
	}
	free_fd_recursive(fds, size, index + 1);
}

void	free_fd(int **fds, int size)
{
	if (fds && size > 0)
		free_fd_recursive(fds, size, 0);
}

void	free_path(char **path)
{
	if (path && *path)
	{
		free(*path);
		*path = NULL;
	}
}

void	stop(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
