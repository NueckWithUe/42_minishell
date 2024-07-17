/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:58:56 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/10 02:29:49 by blatifat         ###   ########.fr       */
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
