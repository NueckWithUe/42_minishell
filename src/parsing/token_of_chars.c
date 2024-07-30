/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_of_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 02:40:53 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/24 03:03:44 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_struct	*handle_less_than(t_lexer_struct *lexer, char next_char)
{
	if (next_char == '<')
	{
		lexer->position += 2;
		return (initialize_token(HEAD_DOC, strdup("<<"), NULL, NULL));
	}
	else
	{
		lexer->position++;
		return (initialize_token('<', strdup("<"), NULL, NULL));
	}
}

t_token_struct	*handle_greater_than(t_lexer_struct *lexer, char next_char)
{
	if (next_char == '>')
	{
		lexer->position += 2;
		return (initialize_token(APP_OUT, strdup(">>"), NULL, NULL));
	}
	else
	{
		lexer->position++;
		return (initialize_token('>', strdup(">"), NULL, NULL));
	}
}

t_token_struct	*handle_special_chars(t_lexer_struct *lexer,
	char current_char, char next_char)
{
	if (current_char == '|')
	{
		lexer->position++;
		return (initialize_token(PIPE, NULL, NULL, NULL));
	}
	if (current_char == '<')
	{
		return (handle_less_than(lexer, next_char));
	}
	if (current_char == '>')
	{
		return (handle_greater_than(lexer, next_char));
	}
	return (NULL);
}

static void	advance_lexer(t_lexer_struct *lexer)
{
	char	current_char;

	while (lexer->position < (int)strlen(lexer->line))
	{
		current_char = lexer->line[lexer->position];
		if (check_if_space(current_char)
			|| current_char == '\\' || current_char == ';')
		{
			lexer->position++;
		}
		else
			break ;
	}
}

t_token_struct	*next_token(t_lexer_struct *lexer)
{
	char			current_char;
	char			next_char;
	t_token_struct	*special_token;

	advance_lexer(lexer);
	if (lexer->position >= (int)strlen(lexer->line))
	{
		return (initialize_token(EOL, NULL, NULL, NULL));
	}
	current_char = lexer->line[lexer->position];
	next_char = lexer->line[lexer->position + 1];
	special_token = handle_special_chars(lexer, current_char, next_char);
	if (special_token)
	{
		return (special_token);
	}
	return (extract_token_word(lexer));
}
