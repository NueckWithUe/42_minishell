/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:14:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/24 03:17:10 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_token(t_token_struct *token, const char *msg)
{
	if (msg)
	{
		printf("%s\n", msg);
	}
	printf("Token type: %d, value: %s\n", token->type, token->value);
}

void	print_list_of_token(t_token_struct *list, const char *msg)
{
	t_token_struct	*cur_token;

	cur_token = list;
	printf("\n%s\n", msg);
	while (cur_token != NULL)
	{
		print_token(cur_token, msg);
		cur_token = cur_token->next;
	}
}

int	tokenize_line(t_lexer_struct *lexer_data, t_minishell_struct *mini)
{
	t_token_struct	*curr;

	curr = mini->token;
	while (curr->type != EOL)
	{
		curr->next = next_token(lexer_data);
		if (!curr->next || curr->next->type == ERROR)
		{
			ft_putendl_fd("minishell: syntax error unclose quotes\n", 2);
			mini->cd_quite = 258;
			free_if_not_null(&lexer_data->line);
			return (0);
		}
		curr->next->prev = curr;
		curr = curr->next;
	}
	if (DEBUG)
		print_list_of_token(mini->token, "TOKENS");
	return (1);
}

int	is_lexically_valid(t_minishell_struct *mini)
{
	t_lexer_struct	lexer_data;
	int				result;

	init_lexer_data(&lexer_data, mini->readline);
	if (!lexer_data.line)
		return (0);
	mini->token = next_token(&lexer_data);
	if (!mini->token)
	{
		free_if_not_null(&lexer_data.line);
		return (0);
	}
	mini->token->prev = NULL;
	result = tokenize_line(&lexer_data, mini);
	free_if_not_null(&lexer_data.line);
	return (result);
}
