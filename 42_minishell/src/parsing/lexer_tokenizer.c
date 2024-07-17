/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blatifat <blatifat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:14:18 by blatifat          #+#    #+#             */
/*   Updated: 2024/07/09 04:07:48 by blatifat         ###   ########.fr       */
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

int	tokenize_line(t_lexer_struct *lexer_data, t_minishell_struct *mini_data)
{
	t_token_struct	*curr;
	/* t_token_struct	*next; */

	curr = mini_data->token;
	while (curr->type != EOL)
	{
		curr->next = next_token(lexer_data);
		if (!curr->next || curr->next->type == ERROR)
		{
			ft_putendl_fd("minishell: syntax error unclose quotes\n", 2);
			mini_data->cd_quite = 258;
			free_if_not_null(lexer_data->line);
			return (0);
		}
		curr->next->prev = curr;
		curr = curr->next;
	}
	if (DEBUG)
		print_list_of_token(mini_data->token, "TOKENS");
	return (1);
}

int	is_lexically_valid(t_minishell_struct *mini_data)
{
	t_lexer_struct	lexer_data;
	int				result;

	init_lexer_data(&lexer_data, mini_data->readline);
	if (!lexer_data.line)
		return (0);
	mini_data->token = next_token(&lexer_data);
	if (!mini_data->token)
	{
		free_if_not_null(lexer_data.line);
		return (0);
	}
	mini_data->token->prev = NULL;
	result = tokenize_line(&lexer_data, mini_data);
	free_if_not_null(lexer_data.line);
	return (result);
}

void test_simple_command() {
    t_minishell_struct mini_data;
    char *input_line = "echo hello word je taiem";

    mini_data.readline = input_line;

    printf("Starting lexical validation...\n");
    if (!is_lexically_valid(&mini_data)) {
        printf("Lexical validation failed.\n");
        return;
    }

    printf("Starting syntax validation...\n");
    if (!validate_syntax(&mini_data)) {
        printf("Syntax validation failed.\n");
        return;
    }

    printf("Starting AST generation...\n");
    if (!generat_ast_cmd_instruct(&mini_data)) {
        printf("AST generation failed.\n");
        return;
    }

    printf("Test Simple Command: AST generation succeeded.\n");
    print_t_ast(mini_data.commands, "Generated AST");

    // Free resources
    free_ast(mini_data.commands);
    free_list_of_token(mini_data.token);
}

// Fonction main pour exécuter le test
/* int main() {
    printf("Running test_simple_command...\n");
    test_simple_command();
    printf("Finished test_simple_command.\n");
    return 0;
} */