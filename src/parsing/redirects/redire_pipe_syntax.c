/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redire_pipe_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:13:39 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 14:13:53 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// Checks for syntax errors around redirection operators (e.g., <, >, >>, <<).

int	redirection_sytx_error(t_token_struct *token)
{
	int	save_stdout;

	if (token->type == '<' || token->type == '>' || token->type == APP_OUT
		|| token->type == HEAD_DOC)
	{
		if ((token->next->type != WORD && token->next->type == EOL)
			|| (!token->prev && token->next->type != WORD))
		{
			save_stdout = dup(STDOUT_FILENO);
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: syntax error near unexpected token, newline\n");
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
			return (0);
		}
	}
	return (1);
}

// Checks for syntax errors around pipe operators (|)

int	pipe_sytx_error(t_token_struct *token)
{
	int	save_stdout;

	if (token->type == PIPE)
	{
		if (!token->prev || !token->next
			|| token->prev->type == PIPE
			|| token->next->type == PIPE
			|| token->next->type == EOL)
		{
			save_stdout = dup(STDOUT_FILENO);
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: syntax error near unexpected token, '|'\n");
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdout);
			return (0);
		}
	}
	return (1);
}

// Validates the entire command syntax for both pipes and redirections.

int	validate_syntax(t_minishell_struct *mini)
{
	t_token_struct	*cur_token;

	cur_token = mini->token;
	while (cur_token != NULL)
	{
		if (!pipe_sytx_error(cur_token) || !redirection_sytx_error(cur_token))
		{
			mini->cd_quite = 2;
			free_list_of_token(mini->token);
			return (0);
		}
		cur_token = cur_token->next;
	}
	return (1);
}
