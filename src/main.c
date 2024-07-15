/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/15 08:37:26 by nnagel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;

	ret = 0;
	input = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	input = readline(">> ");
	tokens = lexer(input);
	// parser(tokens); //check tokens for grammar
	if (ft_strcmp(tokens[0], "env") && ft_strcmp(tokens[1], "EOFToken"))
		print_arr(envp);
	if (ft_strcmp(tokens[0], "exit") && ft_strcmp(tokens[1], "EOFToken"))
		exit(EXIT_SUCCESS); //exit needs to use the last exit status
	if (ft_strchr(input, '|'))
		handle_pipe(tokens);
	if (ft_strcmp(tokens[0], "cd") && ft_strcmp(tokens[1], "EOFToken"))
		ret = cd(tokens[1]); //ret will be the return value in the future
	if (ret == 1)
		return (1);
	free_tokens(tokens);
	return (0);
}
