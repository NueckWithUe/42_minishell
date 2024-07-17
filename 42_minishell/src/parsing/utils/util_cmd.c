/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:25:52 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/13 17:47:48 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_args(t_token_struct *token)
{
	int	count;

	count = 0;
	while (token && token->type != '|' && token->type != EOL)
	{
		if (token->type == '>' || token->type == '<'
			|| token->type == APP_OUT || token->type == HEAD_DOC)
		{
			token = token->next;
		}
		else
			count++;
		token = token->next;
	}
	return (count);
}

int	token_process(t_token_struct **cur_token, t_asset **cur_ast)
{
	if (!(*cur_token)->prev || (*cur_token)->prev->type == '|')
	{
		if (!insert_new_ast_node(cur_token, cur_ast))
		{
			free_ast(*cur_ast);
			return (0);
		}
	}
	else
		*cur_token = (*cur_token)->next;
	return (1);
}
