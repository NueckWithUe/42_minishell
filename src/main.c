/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/09 11:46:49 by nnagel           ###   ########.fr       */
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
	tokens = NULL;
}

static char	**ft_tokenize(char *input, char delimiter)
{
	int		i;
	int		wc;
	char	**tokens;

	i = 0;
	wc = ft_get_wc(input, delimiter);
	tokens = ft_calloc(wc + 2, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (i < wc)
	{
		tokens[i] = ft_strtok(input, delimiter);
		i++;
	}
	tokens[wc] = ft_strdup("EOFToken");
	tokens[wc + 1] = NULL;
	return (tokens);
}

char	**the_lexer(char *input)
{
	char	**tokens;
	int		i;

	i = 0;
	if (input[0] == '\0')
		return (NULL);
	tokens = ft_tokenize(input, ' ');
	return (tokens);
	// parser(tokens);
	free_tokens(tokens);
}

int	main(int argc, char **argv)
{
	int		ret;
	char	*input;
	char	**tokens;

	ret = 0;
	input = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	while (1)
	{
		input = readline(">> ");
		// lexer(input);
		tokens = the_lexer(input);
		if (ft_strcmp(tokens[0], "exit") && ft_strcmp(tokens[1], "EOFToken"))
			exit(EXIT_SUCCESS);
		if (ft_strchr(input, '|'))
			handle_pipe(tokens);
		free_tokens(tokens);
		if (ft_strcmp(tokens[0], "cd") && ft_strcmp(tokens[1], "EOFToken"))
			ret = cd(NULL);
		if (ret == 1)
			break ;
	}
	return (0);
}
