/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:25:52 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:46:41 by blatifat         ###   ########.fr       */
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

int	check_if_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_string_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*init_string(t_minishell_struct *mini, char *s)
{
	char	*result;

	result = ft_strdup(s);
	free_if_not_null(&s);
	if (!result)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	if (access(result, F_OK | X_OK) == 0)
		return (result);
	print_error_msg(mini->commands->args[0], 2, mini);
	free(result);
	return (NULL);
}
