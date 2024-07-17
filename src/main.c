/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/17 11:39:42 by nnagel           ###   ########.fr       */
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

static char	**sanitize_tokens(char **tokens)
{
	char	**sanitized;
	int		i;

	i = 0;
	sanitized = (char **)malloc(sizeof(char *) * array_size(tokens));
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		sanitized[i] = ft_strdup(tokens[i]);
		i++;
	}
	sanitized[i] = NULL;
	return (sanitized);
}

static void	print_tokens(char **tokens, int m, int i)
{
	if (m == 0)
	{
		while (tokens[i] != NULL)
		{
			ft_printf("%s", tokens[i]);
			i++;
		}
	}
	else
	{
		while (tokens[i] != NULL)
		{
			ft_printf("%s\n", tokens[i]);
			i++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;
	char	**saned_tokens;
	int		stop = 0;

	ret = 0;
	input = NULL;
	if (argc >= 2)
		return (1);
	(void)argv;
	while (!stop)
	{
		input = readline(">> ");
		tokens = lexer(input);
		saned_tokens = sanitize_tokens(tokens);
		// parser(tokens); //check tokens for grammar
		if (ft_strcomp(tokens[0], "stop"))
			break ;
		if (ft_strchr(input, '|'))
			handle_pipe(tokens);
		if (ft_strcomp(tokens[0], "echo"))
		{
			if (ft_strcomp(tokens[1], "-n"))
				print_tokens(saned_tokens, 0, 2);
			else
				print_tokens(saned_tokens, 1, 1);
		}
		if (ft_strcomp(tokens[0], "env") && ft_strcomp(tokens[1], "EOFToken"))
			print_arr(envp);
		else if (ft_strcomp(tokens[0], "exit") && ft_strcomp(tokens[1], "EOFToken"))
			exit(EXIT_SUCCESS); //exit needs to use the last exit status
		else if (ft_strcomp(tokens[0], "cd") && !ft_strcomp(tokens[1], "EOFToken"))
			ret = cd(tokens[1]); //ret will be the return value in the future
		free_tokens(tokens);
		free_tokens(saned_tokens);
	}
	return (ret);
}
