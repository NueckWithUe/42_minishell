/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnagel <nnagel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:01:00 by nnagel            #+#    #+#             */
/*   Updated: 2024/07/22 11:08:25 by nnagel           ###   ########.fr       */
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
		tokens[i] = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

static int	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}

static int	print_echo(char **tokens, int start)
{
	int	i;

	i = start;
	while (!ft_strcomp(tokens[i], "EOFToken"))
	{
		if (ft_strcomp(tokens[i + 1], "EOFToken"))
			ft_printf("%s", tokens[i]);
		else
			ft_printf("%s ", tokens[i]);
		i++;
	}
	if (start == 1)
		write(1, "\n", 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	char	**tokens;
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
		// parser(tokens); //check tokens for grammar
		if (ft_strcomp(input, "stop"))
			stop = 1;
		// if (ft_strchr(input, '|'))
		// 	handle_pipe(tokens);
		if (ft_strcomp(tokens[0], "echo"))
		{
			if (ft_strcomp(tokens[1], "-n"))
				ret = print_echo(tokens, 2);
			else
				ret = print_echo(tokens, 1);
		}
		if (ft_strcomp(tokens[0], "env") && ft_strcomp(tokens[1], "EOFToken"))
			ret = print_arr(envp);
		else if (ft_strcomp(tokens[0], "pwd") && ft_strcomp(tokens[1], "EOFToken"))
			ft_printf("%s\n", getenv("PWD"));
		else if (ft_strcomp(tokens[0], "exit") && ft_strcomp(tokens[1], "EOFToken"))
			exit(ret);
		else if (ft_strcomp(tokens[0], "cd"))
			ret = cd(tokens[1]);
		else if (ft_strcomp(tokens[0], "unset") && ft_strcomp(tokens[1], "EOFToken"))
			ret = 0;
		free_tokens(tokens);
	}
	return (ret);
}
