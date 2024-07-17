/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/17 09:04:57 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_minishell_struct	init_data(char **envp)
{
	t_minishell_struct	data;

	data.envp = envp;
	init_lexer_data(&data.lexer_data, NULL);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell_struct	data;
	char				*ret;
	// t_lexer_struct		lexer_data = {NULL, 0, 0, 0};
	t_token_struct		*token;

	data = init_data(envp);
	ret = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	ret = readline(">> ");
	data.lexer_data.line = ret;
	token = extract_token_word(&data.lexer_data);
	if (token->type != ERROR)
	{
		printf("Token: Type = %d, Value = %s\n", token->type, token->value);
	}
	else
	{
		printf("Error: unmatched quotes\n");
	}
	return (0);
}
