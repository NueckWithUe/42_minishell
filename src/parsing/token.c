/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:22:35 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/30 15:35:57 by blatifat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_struct	*initialize_token(t_type type, char *value,
	t_token_struct *next, t_token_struct *prev)
{
	t_token_struct	*result;

	result = (t_token_struct *)malloc(sizeof(t_token_struct));
	if (!result)
		return (NULL);
	result->type = type;
	if (type == PIPE)
		result->value = ft_strdup("|");
	else if (type == APP_OUT)
		result->value = ft_strdup(">>");
	else if (type == HEAD_DOC)
		result->value = ft_strdup("<<");
	else if (type == EOL)
		result->value = ft_strdup("EOL");
	else
		result->value = value;
	result->next = next;
	result->prev = prev;
	return (result);
}

void	parse_quote(t_lexer_struct *lexer_data)
{
	if (lexer_data->line[lexer_data->position] == '\''
		&& !lexer_data->dbl_quote)
	{
		lexer_data->spl_quote = !lexer_data->spl_quote;
	}
	else if (lexer_data->line[lexer_data->position] == '"'
		&& !lexer_data->spl_quote)
	{
		lexer_data->dbl_quote = !lexer_data->dbl_quote;
	}
	lexer_data->position++;
}

void	handle_quotes(t_lexer_struct *lexer)
{
	char	c;

	c = lexer->line[lexer->position];
	while (lexer->line[lexer->position])
	{
		if (c == '\'' || c == '"')
		{
			parse_quote(lexer);
		}
		else if (!lexer->dbl_quote && !lexer->spl_quote)
		{
			if (check_if_space(c) || c == '|' || c == '>'
				|| c == '<')
				break ;
		}
		else
			lexer->position++;
	}
}

void	handle_quotesss(t_lexer_struct *lexer, char *quote_char)
{
	if (lexer->line[lexer->position] == '\''
		|| lexer->line[lexer->position] == '"')
	{
		*quote_char = lexer->line[lexer->position];
		lexer->position++;
	}
	while (lexer->line[lexer->position])
	{
		if (*quote_char)
		{
			if (lexer->line[lexer->position] == *quote_char)
				break ;
		}
		else
		{
			if (check_if_space(lexer->line[lexer->position]))
				break ;
		}
		if (lexer->line[lexer->position] == '\\' && *quote_char != '\'')
			lexer->position++;
		lexer->position++;
	}
	if (*quote_char && lexer->line[lexer->position] == *quote_char)
		lexer->position++;
}

t_token_struct	*extract_token_word(t_lexer_struct *lexer)
{
	int		start;
	char	quote_char;
	char	*value;
	int		length;

	start = lexer->position;
	quote_char = 0;
	handle_quotesss(lexer, &quote_char);
	length = lexer->position - start;
	if (length <= 0)
		return (NULL);
	value = strndup(lexer->line + start, length);
	printf("Extracted word: %s, New position: %d\n", value, lexer->position);
	return (initialize_token(WORD, value, NULL, NULL));
}
