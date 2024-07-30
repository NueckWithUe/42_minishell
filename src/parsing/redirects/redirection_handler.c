/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:58:56 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/24 05:45:17 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handl_redirection(t_token_struct **cur_token, t_asset *new_node)
{
	if ((*cur_token)->type == '>')
	{
		*cur_token = (*cur_token)->next;
		new_node->fd_outfile = open((*cur_token)->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if ((*cur_token)->type == APP_OUT)
	{
		*cur_token = (*cur_token)->next;
		new_node->fd_outfile = open((*cur_token)->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if ((*cur_token)->type == '<')
	{
		*cur_token = (*cur_token)->next;
		new_node->fd_outfile = open((*cur_token)->value, O_WRONLY);
	}
	else if ((*cur_token)->type == HEAD_DOC)
		*cur_token = (*cur_token)->next;
	else
		return (0);
	*cur_token = (*cur_token)->next;
	return (1);
}

int	add_args(t_token_struct **cur_token, t_asset *new_node)
{
	int	i;

	i = 0;
	while (*cur_token && (*cur_token)->type != EOL && (*cur_token)->type != '|')
	{
		if (!handl_redirection(cur_token, new_node))
		{
			new_node->args[i] = ft_strdup((*cur_token)->value);
			i++;
			*cur_token = (*cur_token)->next;
		}
	}
	new_node->args[i] = NULL;
	return (1);
}

int	check_file_type(const char *path)
{
	struct stat	floder;

	if (stat(path, &floder) == 0)
	{
		if (S_ISDIR(floder.st_mode))
		{
			ft_putstr_fd("minishell ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	verify_file_access(const char *path)
{
	struct stat	floder;

	if (stat(path, &floder) == 0)
	{
		if (access(path, R_OK) == -1)
		{
			ft_putstr_fd("minishell", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}
