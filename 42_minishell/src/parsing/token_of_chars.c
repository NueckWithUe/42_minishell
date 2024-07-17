/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_of_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 02:40:53 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/09 04:05:05 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	check_if_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_token_struct	*handle_less_than(t_lexer_struct *lexer, char next_char)
{
	if (next_char == '<')
	{
		lexer->position += 2;
		return (initialize_token(HEAD_DOC, NULL, NULL, NULL));
	}
	else
	{
		lexer->position++;
		return (initialize_token('<', NULL, NULL, NULL));
	}
}

t_token_struct	*handle_greater_than(t_lexer_struct *lexer, char next_char)
{
	if (next_char == '>')
	{
		lexer->position += 2;
		return (initialize_token(APP_OUT, NULL, NULL, NULL));
	}
	else
	{
		lexer->position++;
		return (initialize_token('>', NULL, NULL, NULL));
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

t_token_struct	*next_token(t_lexer_struct *lexer)
{
	char			current_char;
	char			next_char;
	t_token_struct	*special_token;

	while (lexer->position < (int)ft_strlen(lexer->line))
	{
		current_char = lexer->line[lexer->position];
		next_char = lexer->line[lexer->position + 1];
		if (check_if_space(current_char))
			lexer->position++;
		else if (current_char == '\\' || current_char == ';')
			lexer->position++;
		else
		{
			special_token
				= handle_special_chars(lexer, current_char, next_char);
			if (special_token)
				return (special_token);
		}
		if (!check_if_space(current_char))
			return (extract_token_word(lexer));
	}
	return (initialize_token(EOL, NULL, NULL, NULL));
}

/* int main() {
    char input_line[] = "echo 'Hello hi' \"World how are you me\" > output.txt";
    t_lexer_struct lexer_data = {input_line, 0, 0, 0};
    t_token_struct *token;

    while ((token = next_token(&lexer_data))->type != EOL) {
        printf("Token: Type = %d, Value = %s\n", token->type, token->value ? token->value : "NULL");
        free(token->value);
        free(token);
    }

    return 0;
} */